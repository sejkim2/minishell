# Memory Management

## 1. 개요

Minishell은 C 언어로 구현되어 있기 때문에 Java와 같은 GC(Garbage Collector)가 존재하지 않습니다.

따라서 `malloc()`으로 동적으로 할당한 메모리는 **사용이 끝난 시점에 직접 `free()`해야 합니다.**

이 프로젝트에서는 명령어를 처리하는 과정에서 생성되는 자료구조를 각각 관리하고, 작업이 끝난 뒤 전용 해제 함수를 호출하여 메모리를 정리합니다.

전체적인 흐름은 다음과 같습니다.

```text
사용자 입력
    ↓
readline()
    ↓
Lexer
    ↓
Token Linked List 생성
    ↓
Parser
    ↓
Command Tree 생성
    ↓
Command 실행
    ↓
Tree 해제
    ↓
다음 명령어
```

즉, **명령어 하나를 처리하는 데 필요한 메모리를 생성하고, 해당 명령어의 실행이 끝나면 정리하는 구조**입니다.

---

## 2. 명령어 입력부터 메모리 해제까지

`main.c`의 `read_command_line()`을 중심으로 보면 메모리의 생명주기를 확인할 수 있습니다.

```c
line = readline("minishell$ ");

list = lexer(line);

root = parser(list, *env);

free_list(list, 0);

run_root(root, env);

free_tree(root, 1);
```

그리고 `main()`에서는 명령어 처리가 끝난 후 `readline()`이 반환한 문자열도 직접 해제합니다.

```c
line = read_command_line(&env);

if (line)
    free(line);
```

따라서 하나의 명령어에 대한 주요 메모리 생명주기는 다음과 같습니다.

```text
readline()
    │
    ├── line
    │
    ↓
lexer()
    │
    ├── linked list
    ├── token
    └── token 내부 문자열
    │
    ↓
parser()
    │
    └── tree
         └── token
              ├── value
              ├── str_info
              └── heredoc name
    │
    ↓
run_root()
    │
    ↓
free_tree()
    │
    └── tree 관련 메모리 해제
    │
    ↓
free(line)
```

`main.c`에서는 실제로 `lexer → parser → free_list → run_root → free_tree → free(line)` 순서로 처리하고 있습니다.

---

## 3. Lexer의 메모리 관리

Lexer에서는 입력 명령어를 Token Linked List로 변환합니다.

프로젝트의 `lexer_dir`에는 다음과 같이 메모리 관리를 담당하는 `free_list.c`가 별도로 존재합니다.

```text
srcs/
└── lexer_dir/
    ├── lexer.c
    ├── tokenize.c
    ├── list_utils.c
    ├── list_node_utils.c
    └── free_list.c
```

Lexer에서 Token을 만들 때 동적으로 메모리를 할당합니다.

### Token 생성

`list_node_utils.c`의 `make_token()`에서는 Token 구조체 자체를 동적으로 할당합니다.

```c
new_token = (t_token *)malloc(sizeof(t_token));
```

그리고 Token을 Linked List에 연결하기 위한 Node도 별도로 할당합니다.

```c
new_node = (t_token_node *)malloc(sizeof(t_token_node));
```

즉, 하나의 Token을 관리하기 위해 최소한 다음과 같은 동적 메모리가 발생합니다.

```text
Token
 │
 ├── t_token
 │
 └── t_token_node
```

---

## 4. Token 내부 메모리까지 해제

중요한 점은 `free(token)`만 호출해서는 충분하지 않다는 것입니다.

Token 내부에도 동적으로 할당된 데이터가 존재하기 때문입니다.

프로젝트에서는 이를 `free_token()`에서 처리합니다.

```text
t_token
 ├── value
 ├── str_info
 │    └── str
 ├── hd_name
 └── t_token 자체
```

해제 순서는 다음과 같습니다.

```text
1. token->value
        ↓
2. token->str_info 내부의 문자열
        ↓
3. token->str_info
        ↓
4. token->hd_name
        ↓
5. token
```

`free_token()`에서는 실제로 `value`, `str_info` 내부 문자열, `str_info`, `hd_name`, 그리고 마지막으로 Token 자체를 순서대로 해제합니다.

특히 `hd_name`은 단순히 메모리만 해제하는 것이 아니라,

```c
unlink(token->hd_name);
free(token->hd_name);
```

와 같이 **heredoc에서 생성된 임시 파일까지 제거한 후 문자열 메모리를 해제**합니다.

따라서 이 프로젝트의 자원 관리는 메모리뿐만 아니라 임시 파일까지 고려하고 있습니다.

---

## 5. Linked List 전체 해제

Token 하나만 해제하는 것이 아니라 Lexer가 생성한 전체 Linked List를 해제해야 합니다.

이를 담당하는 함수가 `free_list()`입니다.

```text
Linked List

head
 ↓
Node → Node → Node → Node
 ↓      ↓      ↓      ↓
Token  Token  Token  Token
```

`free_list()`는 List의 Node를 순회하면서 각각을 삭제합니다.

```text
free_list()
    ↓
각 Node 탐색
    ↓
free_token_node()
    ↓
free_token()
    ↓
free(Node)
    ↓
마지막으로 free(List)
```

즉, 단순히 List의 head만 `free()`하는 것이 아니라 **Node → Token → Token 내부 데이터 → List**의 계층 구조를 따라가면서 전체 메모리를 해제합니다.

---

## 6. 에러가 발생한 경우에도 메모리 해제

이 프로젝트에서 중요한 부분 중 하나는 **정상적인 실행뿐만 아니라 Lexer 단계에서 에러가 발생했을 때도 이미 할당된 메모리를 정리한다는 점**입니다.

`lexer()`에서는 Token 생성에 실패하거나 문법 검증에서 문제가 발생하면 `free_list()`를 호출합니다.

```c
node = tokenize(cmd_line, &i);

if (node == 0)
{
    free_list(list, 1);
    return (0);
}
```

또한 빈 명령어나 괄호 관련 오류가 발생한 경우에도,

```c
free_list(list, 1);
```

를 호출합니다.

즉,

```text
정상적인 경우
    ↓
Token 생성
    ↓
Parser로 전달
    ↓
사용 후 free

에러 발생
    ↓
이미 생성된 Token 존재
    ↓
free_list()
    ↓
기존 메모리 정리
    ↓
실행 종료
```

와 같은 구조입니다.

이것은 **에러 발생 시 발생하는 메모리 누수(memory leak)를 방지하기 위한 처리**입니다.

---

## 7. Parser의 Tree 메모리 관리

Parser에서는 Token Linked List를 기반으로 실행할 명령 구조를 Tree 형태로 구성합니다.

따라서 Lexer에서 사용한 Linked List와 별도로 Tree에 대한 메모리 관리가 필요합니다.

프로젝트에서는 이를 `parser_dir/free_tree.c`에서 담당합니다.

```text
srcs/
└── parser_dir/
    ├── parser.c
    ├── tree_node_utils.c
    └── free_tree.c
```

Parser가 만든 Tree는 다음과 같은 구조로 생각할 수 있습니다.

```text
             Tree
              │
        ┌─────┴─────┐
        │           │
      Node         Node
        │           │
      Token       Token
        │
   ┌────┴────┐
 value    str_info
```

따라서 Tree를 해제할 때도 단순히 root만 `free()`하면 안 됩니다.

---

## 8. Tree를 재귀적으로 해제

`free_tree()`는 Tree의 child node를 따라가면서 하위 Tree를 먼저 정리합니다.

개념적으로 다음과 같은 방식입니다.

```text
free_tree(root)
    │
    ├── child 1
    │    ├── child
    │    └── child
    │
    ├── child 2
    │
    └── child 3
```

각 Node에 더 이상 child가 없으면 `free_tree_node()`를 호출합니다.

```text
Leaf Node
    ↓
free_token()
    ↓
free(node)
```

그리고 하위 Node들을 모두 처리한 후 부모 Node를 해제합니다.

즉, **Tree의 하위 요소부터 상위 요소 순서로 메모리를 해제하는 방식**입니다.

---

## 9. Tree 해제 순서

전체적으로 보면 다음과 같습니다.

```text
                    Root
                     │
             ┌───────┴───────┐
             ↓               ↓
           Node             Node
             │
        ┌────┴────┐
        ↓         ↓
      Node       Node
        │
      Token
        │
   ┌────┼────┐
   ↓    ↓    ↓
 value str_info hd_name
```

해제할 때는 반대 방향으로 진행합니다.

```text
value
  ↓
str_info 내부 문자열
  ↓
str_info
  ↓
hd_name + heredoc 파일
  ↓
Token
  ↓
Leaf Node
  ↓
Child Node
  ↓
Root
```

이러한 방식으로 **하위 객체를 먼저 해제한 뒤 상위 객체를 해제**합니다.

---

## 10. 하나의 명령어를 처리할 때의 전체 메모리 흐름

이 프로젝트의 메모리 관리를 가장 쉽게 이해하는 방법은 명령어 하나를 기준으로 보는 것입니다.

예를 들어 다음 명령어가 입력되었다고 가정합니다.

```bash
echo hello | grep hello
```

### Step 1. 입력 문자열 생성

```text
readline()
    ↓
"echo hello | grep hello"
```

`readline()`이 반환한 문자열은 `line`이 가리킵니다.

---

### Step 2. Lexer에서 Token 생성

```text
line
 ↓
lexer()
 ↓
Linked List

Token → Token → Token → Token → ...
```

각 Token과 Node는 `malloc()`으로 동적 할당됩니다.

---

### Step 3. Parser에서 Tree 생성

```text
Linked List
    ↓
parser()
    ↓
Command Tree
```

Parser가 실행 구조를 Tree로 구성합니다.

---

### Step 4. Lexer 자료구조 해제

Parser가 Tree를 생성한 이후에는 Lexer에서 사용하던 List를 더 이상 필요로 하지 않습니다.

따라서

```c
free_list(list, 0);
```

를 호출하여 Linked List를 해제합니다.

여기서 중요한 것은 **각 자료구조가 필요한 시점까지만 살아 있도록 관리한다는 것**입니다.

```text
Lexer
  │
  │ Linked List 필요
  ↓
Parser
  │
  │ Tree 생성 완료
  ↓
Linked List 더 이상 필요 없음
  │
  ↓
free_list()
```

---

### Step 5. Command 실행

```text
Tree
 ↓
run_root()
 ↓
Command 실행
```

Tree는 실행에 필요한 동안 유지됩니다.

---

### Step 6. 실행 종료 후 Tree 해제

실행이 끝나면 더 이상 Tree가 필요하지 않습니다.

따라서

```c
free_tree(root, 1);
```

을 호출합니다.

```text
Command 실행
    ↓
실행 완료
    ↓
Tree 필요 없음
    ↓
free_tree()
```

---

### Step 7. readline 문자열 해제

마지막으로 `readline()`이 반환했던 입력 문자열도 해제합니다.

```c
free(line);
```

---

## 11. 핵심 설계 방식

이 프로젝트의 메모리 관리 방식은 크게 **자료구조별 해제 함수**와 **명령어 단위의 생명주기 관리**로 정리할 수 있습니다.

### 자료구조별 해제 함수

```text
Token Linked List
        ↓
   free_list()

Token
        ↓
   free_token()

Command Tree
        ↓
   free_tree()

Tree Node
        ↓
free_tree_node()
```

각 자료구조에 대한 해제 책임을 별도의 함수로 분리했습니다.

---

### 명령어 단위의 생명주기

```text
┌──────────────────────────────┐
│       하나의 명령어 입력       │
├──────────────────────────────┤
│                              │
│  readline                    │
│      ↓                       │
│  Token List 생성              │
│      ↓                       │
│  Command Tree 생성            │
│      ↓                       │
│  Token List 해제              │
│      ↓                       │
│  Command 실행                 │
│      ↓                       │
│  Command Tree 해제            │
│      ↓                       │
│  readline 문자열 해제          │
│                              │
└──────────────────────────────┘
```

따라서 이전 명령어의 실행에 사용했던 메모리를 계속 유지하는 것이 아니라, **한 명령어의 처리가 끝나면 해당 명령어에 필요한 메모리를 정리하고 다음 명령어를 처리**합니다.

---

## 12. 정리

이 프로젝트의 메모리 관리 핵심은 다음과 같습니다.

1. **동적으로 생성되는 자료구조를 명확하게 분리합니다.**

   * Token
   * Token Node
   * Linked List
   * Tree Node
   * Token 내부 문자열

2. **자료구조마다 전용 해제 함수를 제공합니다.**

   * `free_token()`
   * `free_token_node()`
   * `free_list()`
   * `free_tree_node()`
   * `free_tree()`

3. **하위 데이터부터 해제합니다.**

```text
내부 문자열
    ↓
Token
    ↓
Node
    ↓
List / Tree
```

4. **에러가 발생해도 이미 할당된 메모리를 정리합니다.**

5. **명령어 단위로 메모리의 생명주기를 관리합니다.**

```text
Allocate
   ↓
Use
   ↓
Free
   ↓
다음 명령어
```

결국 이 프로젝트의 메모리 관리 방식은 **C 언어의 수동 메모리 관리 특성을 고려하여, 자료구조의 생성과 해제를 대응시키고 명령어 처리 단계가 끝날 때 더 이상 필요하지 않은 메모리를 즉시 회수하는 방식**이라고 정리할 수 있습니다.
