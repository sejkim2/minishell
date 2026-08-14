
# Lexer & Parser

Minishell에서 입력된 명령어가 실제로 실행되기까지는 크게 다음과 같은 과정을 거칩니다.

```text
사용자 입력
    │
    ▼
  Lexer
    │
    ▼
Token Linked List
    │
    ▼
  Parser
    │
    ▼
Command Tree
    │
    ▼
Executor
```

Lexer와 Parser를 분리하는 이유는 **문자열을 의미 있는 단위로 나누는 작업**과 **그 단위들의 문법적 관계를 해석하는 작업**이 서로 다르기 때문입니다.

* **Lexer**: 입력 문자열을 Token으로 분리합니다.
* **Parser**: Token들의 관계를 분석하여 실행 가능한 Tree를 구성합니다.

---

## 1. 왜 Lexer와 Parser가 필요한가?

사용자가 다음과 같은 명령어를 입력했다고 가정합니다.

```bash
echo hello | grep hello > result.txt
```

입력 자체는 단순한 문자열이지만 Shell 입장에서는 다음과 같은 의미를 가지고 있습니다.

```text
echo hello
      │
      └── 명령어 인자

|
└── Pipe

grep hello
     │
     └── 또 다른 명령어

>
└── Redirection

result.txt
└── Redirection 대상
```

따라서 Shell은 먼저 문자열을 의미 있는 단위로 분리해야 합니다.

```text
"echo hello | grep hello > result.txt"

                ↓ Lexer

WORD        : echo
WORD        : hello
PIPE        : |
WORD        : grep
WORD        : hello
REDIRECTION : >
WORD        : result.txt
```

하지만 Token으로 분리하는 것만으로는 충분하지 않습니다.

Parser는 이 Token들의 관계를 분석하여

```text
echo hello
    │
    PIPE
    │
grep hello
    │
    └── > result.txt
```

와 같은 **명령어의 구조**를 만들어야 합니다.

즉,

```text
Lexer  → "무엇인가?"
Parser → "어떤 관계인가?"
```

라고 생각할 수 있습니다.

---

# 2. Lexer

## 2.1 Lexer의 역할

Lexer는 입력 문자열을 처음부터 순회하면서 Shell에서 의미를 가지는 단위인 **Token**으로 변환합니다.

프로젝트에서는 `lexer_dir`에서 이 기능을 구현하고 있습니다.

```text
lexer_dir/
├── lexer.c
├── tokenize.c
├── parse_pipe_or_orif_or_andif.c
├── parse_redirection.c
├── parse_word_or_branket.c
├── parse_quote_string.c
├── make_quote_string.c
├── make_value.c
└── ...
```

전체적인 흐름은 다음과 같습니다.

```text
입력 문자열
    │
    ▼
  lexer()
    │
    ▼
 tokenize()
    │
    ├── Operator
    │
    ├── Bracket
    │
    └── Word
    │
    ▼
Token Linked List
```

---

## 2.2 `lexer()`

`lexer.c`의 `lexer()`는 Lexer의 전체적인 흐름을 제어합니다.

입력 문자열을 처음부터 끝까지 순회하면서 `tokenize()`를 호출하고, 반환된 Token을 Linked List에 추가합니다.

개념적으로 다음과 같은 구조입니다.

```c
while (cmd_line[i])
{
    while (cmd_line[i] && check_is_white_space(cmd_line[i]))
        i++;

    node = tokenize(cmd_line, &i);

    push_back_list(list, node);
}
```

따라서 `lexer()`의 역할은 크게 두 가지입니다.

1. 입력 문자열을 순회합니다.
2. 현재 위치의 문자열을 `tokenize()`를 통해 Token으로 변환합니다.

최종적으로 Parser가 사용할 **Token Linked List**를 만들어냅니다.

---

# 3. Token의 종류

Lexer가 만들어내는 Token은 크게 다음과 같이 구분할 수 있습니다.

```text
Token
├── WORD
├── PIPE
├── OR_IF
├── AND_IF
├── REDIRECTION
├── L_BRA
└── R_BRA
```

예를 들어,

```bash
echo hello | grep hello > result.txt
```

는 다음과 같이 Token화할 수 있습니다.

```text
WORD        : echo
WORD        : hello
PIPE        : |
WORD        : grep
WORD        : hello
REDIRECTION : >
WORD        : result.txt
```

중요한 점은 Lexer 단계에서는 아직

> `echo`와 `grep`이 Pipe로 연결된다.

라는 문법적 관계를 해석하지 않는다는 것입니다.

Lexer는 단지 각각의 문자열이 **어떤 종류의 Token인지 판별**합니다.

---

# 4. `tokenize()`의 분기

Lexer의 핵심 함수 중 하나가 `tokenize()`입니다.

현재 문자를 확인한 뒤 어떤 종류의 Token으로 만들어야 하는지 판단합니다.

개념적으로 다음과 같은 구조입니다.

```text
                     tokenize()
                         │
          ┌──────────────┼──────────────┐
          │              │              │
       Operator        Bracket         Word
          │              │              │
          ▼              ▼              ▼
   Redirection       ( / )          일반 문자열
   Pipe              L_BRA          Quote 처리
   OR_IF             R_BRA
   AND_IF
```

예를 들어 현재 문자가 `<` 또는 `>`라면 Redirection으로 처리합니다.

```text
<
>
<<
>>
```

현재 문자가 `|` 또는 `&`라면 Pipe 또는 AND/OR 연산자로 처리합니다.

```text
|
||
&&
```

그 외의 일반적인 문자열은 `WORD`로 처리합니다.

---

# 5. Quote 처리

Shell의 Lexer를 구현할 때 중요한 부분 중 하나가 Quote입니다.

예를 들어 다음 명령어를 생각해 볼 수 있습니다.

```bash
echo "hello world"
```

단순하게 공백을 기준으로 문자열을 분리한다면 다음과 같이 잘못 처리할 수 있습니다.

```text
echo
"hello
world"
```

하지만 Shell에서는 `"hello world"` 전체가 하나의 Word입니다.

```text
WORD : echo
WORD : "hello world"
```

따라서 프로젝트에서는 Word를 파싱할 때 Quote를 별도로 처리합니다.

```text
parse_word()
     │
     ├── 일반 문자
     │      └── 계속 parsing
     │
     ├── '
     │      └── Single Quote 처리
     │
     └── "
            └── Double Quote 처리
```

즉 Lexer는 단순히 공백으로 문자열을 나누는 것이 아니라 **Quote를 고려하여 하나의 Word가 어디까지인지 판단**합니다.

---

# 6. Redirection 처리

Shell에서 사용하는 Redirection은 다음과 같습니다.

```bash
<
>
<<
>>
```

예를 들어,

```bash
cat < input.txt
```

를 입력하면 Lexer는 다음과 같이 Token을 생성합니다.

```text
WORD        : cat
REDIRECTION : <
WORD        : input.txt
```

또한,

```bash
cat > output.txt
```

라면

```text
WORD        : cat
REDIRECTION : >
WORD        : output.txt
```

가 됩니다.

프로젝트에서는 `parse_redirection()`을 통해 Redirection을 처리합니다.

Redirection 뒤에 오는 파일 이름 역시 일반적인 문자열과 마찬가지로 Quote를 고려해야 합니다.

예를 들어,

```bash
cat < "hello world.txt"
```

에서는

```text
REDIRECTION : <
WORD        : "hello world.txt"
```

가 되어야 합니다.

---

# 7. Pipe / AND / OR 처리

Shell에서는 여러 명령어를 연결하기 위해 다음과 같은 연산자를 사용합니다.

```bash
|
||
&&
```

프로젝트에서는 `parse_pipe_or_orif_or_andif()`를 통해 이를 구분합니다.

### `|`

```bash
ls | grep txt
```

```text
PIPE
```

### `||`

```bash
make || echo "build failed"
```

```text
OR_IF
```

### `&&`

```bash
make && ./program
```

```text
AND_IF
```

특히 `|`를 만났을 때 다음 문자도 `|`인지 확인하여 `PIPE`와 `OR_IF`를 구분합니다.

```text
'|'
 │
 ├── 다음 문자도 '|'
 │       └── OR_IF
 │
 └── 그렇지 않음
         └── PIPE
```

마찬가지로 `&`는 다음 문자가 `&`인지 확인하여 `AND_IF`를 판단합니다.

---

# 8. Lexer의 최종 결과

예를 들어 다음 명령어를 입력했다고 가정합니다.

```bash
cat input.txt | grep hello > result.txt
```

Lexer의 결과는 다음과 같습니다.

```text
┌────────────┐
│ WORD       │ cat
└────────────┘
       ↓
┌────────────┐
│ WORD       │ input.txt
└────────────┘
       ↓
┌────────────┐
│ PIPE       │ |
└────────────┘
       ↓
┌────────────┐
│ WORD       │ grep
└────────────┘
       ↓
┌────────────┐
│ WORD       │ hello
└────────────┘
       ↓
┌────────────┐
│ REDIRECTION│ >
└────────────┘
       ↓
┌────────────┐
│ WORD       │ result.txt
└────────────┘
```

이 결과가 Parser의 입력이 됩니다.

즉,

```text
입력 문자열
    ↓
  Lexer
    ↓
Token Linked List
    ↓
  Parser
```

의 구조가 만들어집니다.

---

# 9. Parser

## 9.1 Parser의 역할

Lexer가 문자열을 Token으로 분리했다면 Parser는 Token 사이의 **문법적인 관계**를 분석합니다.

예를 들어 다음 Token들이 있다고 가정합니다.

```text
WORD echo
WORD hello
PIPE
WORD grep
WORD hello
REDIRECTION >
WORD result.txt
```

Parser는 단순히 Token을 나열하는 것이 아니라 다음과 같은 구조를 만들어야 합니다.

```text
            PIPELINE
           /        \
     COMMAND       COMMAND
       /              \
     echo            grep
     hello           hello
                       │
                  REDIRECTION
                       │
                   result.txt
```

즉 Parser의 최종 결과는 **Command Tree**입니다.

---

# 10. BNF와 Recursive Descent Parsing

Parser를 구현하기 위해서는 Shell 문법을 계층적으로 표현할 필요가 있습니다.

참고한 문법의 핵심적인 구조는 다음과 같이 볼 수 있습니다.

```text
LIST
 └── PIPELINE
      └── COMMAND
           └── SIMPLE_COMMAND
```

그리고 각 문법 요소를 Parser의 함수와 대응시킬 수 있습니다.

```text
문법              Parser 함수

LIST          →   parse_list()
PIPELINE      →   parse_pipeline()
COMMAND       →   parse_command()
SIMPLE_COMMAND→   parse_simple_command()
```

이러한 방식을 **Recursive Descent Parsing(재귀 하향 파싱)**이라고 할 수 있습니다.

즉 문법의 계층 구조를 Parser 함수의 호출 구조로 직접 표현합니다.

```text
parse_list()
    │
    ▼
parse_pipeline()
    │
    ▼
parse_command()
    │
    ▼
parse_simple_command()
```

이 방식의 장점은 Shell의 문법 구조와 실제 코드의 구조가 직접적으로 대응된다는 것입니다.

---

# 11. Parser의 시작점

Parser의 시작점은 `parser()`입니다.

전체적인 구조는 다음과 같습니다.

```text
parser()
   │
   ▼
 ROOT
   │
   ▼
 LIST
```

즉 Tree의 최상위에 `ROOT`를 만들고 그 아래에 `LIST`를 구성합니다.

```text
ROOT
 └── LIST
```

이후 `parse_list()`가 Token을 분석하면서 실제 명령어 구조를 만들어 나갑니다.

---

# 12. LIST → PIPELINE

`LIST`는 하나 이상의 Pipeline을 포함할 수 있습니다.

예를 들어,

```bash
ls
```

라면:

```text
LIST
 └── PIPELINE
      └── COMMAND
           └── ls
```

가 됩니다.

`&&`나 `||`를 사용하면 여러 Pipeline이 연결될 수 있습니다.

```bash
ls && pwd
```

개념적으로 다음과 같은 구조가 됩니다.

```text
LIST
├── PIPELINE
│    └── COMMAND
│         └── ls
│
├── AND_IF
│
└── PIPELINE
     └── COMMAND
          └── pwd
```

즉 Parser는 `AND_IF`, `OR_IF`를 기준으로 Pipeline들을 연결합니다.

---

# 13. PIPELINE → COMMAND

Pipeline은 Pipe(`|`)로 연결된 Command들의 구조입니다.

예를 들어,

```bash
ls | grep txt
```

는 다음과 같이 표현할 수 있습니다.

```text
PIPELINE
├── COMMAND
│    └── ls
│
├── PIPE
│
└── COMMAND
     └── grep txt
```

프로젝트에서는 Pipe를 만나면 새로운 Pipeline/Command 구조를 만들기 위해 `parse_pipeline()`이 재귀적으로 호출됩니다.

따라서 여러 개의 Pipe도 자연스럽게 처리할 수 있습니다.

```bash
ls | grep txt | wc -l
```

```text
PIPELINE
├── COMMAND
│    └── ls
│
├── PIPE
│
└── PIPELINE
     ├── COMMAND
     │    └── grep txt
     │
     ├── PIPE
     │
     └── PIPELINE
          └── COMMAND
               └── wc -l
```

---

# 14. COMMAND → SIMPLE_COMMAND

Command 내부에서는 실제 명령어와 인자, Redirection 등을 처리합니다.

예를 들어,

```bash
echo hello > result.txt
```

는 다음과 같이 구성할 수 있습니다.

```text
COMMAND
└── SIMPLE_COMMAND
    ├── WORD : echo
    ├── WORD : hello
    │
    └── REDIRECTION
         ├── >
         └── WORD : result.txt
```

프로젝트의 `parse_simple_command()`에서는 `WORD`와 `REDIRECTION`을 기준으로 실제 Simple Command를 구성합니다.

여기서 중요한 점은 **Lexer가 이미 Token을 만들어 놓았기 때문에 Parser는 문자 하나하나를 다시 분석할 필요가 없다는 것**입니다.

Parser는 다음과 같은 Token을 보고

```text
WORD
WORD
REDIRECTION
WORD
```

각 Token이 Command 내부에서 어떤 역할을 하는지를 판단합니다.

---

# 15. LCRS Tree

Parser에서 생성하는 Tree는 일반적인 Binary Tree와 조금 다른 방식으로 구성됩니다.

프로젝트에서는 Tree Node의 `child_list`와 `next`를 이용하여 **LCRS(Left Child, Right Sibling)** 형태로 여러 자식을 표현합니다.

기본적인 구조는 다음과 같습니다.

```text
Parent
   │
   └── child_list
          │
          ▼
        Child 1
          │
         next
          ▼
        Child 2
          │
         next
          ▼
        Child 3
```

즉,

* `child_list`: 첫 번째 자식
* `next`: 같은 부모를 가진 다음 형제

를 의미합니다.

---

# 16. 왜 LCRS를 사용하는가?

Shell의 문법 구조에서는 하나의 노드가 여러 개의 자식을 가질 수 있습니다.

예를 들어:

```bash
echo hello world
```

의 Simple Command는 여러 개의 Word를 가질 수 있습니다.

```text
SIMPLE_COMMAND
├── echo
├── hello
└── world
```

이를 LCRS 구조로 표현하면 다음과 같습니다.

```text
SIMPLE_COMMAND
      │
      ▼
     echo
      │
     next
      ▼
    hello
      │
     next
      ▼
    world
```

이렇게 하면 일반적인 Binary Tree 구조를 이용하면서도 **가변적인 개수의 자식 노드**를 표현할 수 있습니다.

프로젝트에서는 Tree Node의 `child_list`와 `next`를 이용하여 이 구조를 구현하고 있습니다.

---

# 17. 실제 예제로 전체 과정 확인

이제 Lexer와 Parser의 전체 과정을 하나의 명령어로 확인할 수 있습니다.

입력:

```bash
echo hello | grep hello > result.txt
```

## Step 1. Lexer

입력 문자열을 순회합니다.

```text
echo hello | grep hello > result.txt
```

↓

```text
WORD        : echo
WORD        : hello
PIPE        : |
WORD        : grep
WORD        : hello
REDIRECTION : >
WORD        : result.txt
```

---

## Step 2. Token Linked List

Token들은 Linked List 형태로 연결됩니다.

```text
[WORD echo]
      ↓
[WORD hello]
      ↓
[PIPE]
      ↓
[WORD grep]
      ↓
[WORD hello]
      ↓
[REDIRECTION >]
      ↓
[WORD result.txt]
```

이제 Parser가 이 Token List를 입력으로 받습니다.

---

## Step 3. `parser()`

Parser가 시작되면서 Root를 생성합니다.

```text
ROOT
 └── LIST
```

---

## Step 4. `parse_list()`

먼저 Pipeline을 파싱합니다.

```text
ROOT
 └── LIST
      └── PIPELINE
```

---

## Step 5. `parse_pipeline()`

첫 번째 Command를 파싱합니다.

```text
ROOT
 └── LIST
      └── PIPELINE
           └── COMMAND
                └── SIMPLE_COMMAND
                     ├── echo
                     └── hello
```

이후 `PIPE` Token을 발견합니다.

```text
PIPE
```

따라서 다음 Command를 파싱합니다.

---

## Step 6. 두 번째 Command

```text
PIPELINE
├── COMMAND
│    └── SIMPLE_COMMAND
│         ├── echo
│         └── hello
│
├── PIPE
│
└── COMMAND
     └── SIMPLE_COMMAND
          ├── grep
          └── hello
```

그리고 두 번째 Command에서 `REDIRECTION`을 발견합니다.

```text
>
result.txt
```

이를 Command Tree에 추가합니다.

---

## Step 7. 최종 Tree

최종적으로 다음과 같은 구조를 만들 수 있습니다.

```text
ROOT
└── LIST
     └── PIPELINE
          ├── COMMAND
          │    └── SIMPLE_COMMAND
          │         ├── WORD : echo
          │         └── WORD : hello
          │
          ├── PIPE
          │
          └── COMMAND
               └── SIMPLE_COMMAND
                    ├── WORD : grep
                    ├── WORD : hello
                    │
                    └── REDIRECTION
                         ├── >
                         └── WORD : result.txt
```

이제 Executor는 이 Tree를 이용하여 실제 실행 순서를 결정할 수 있습니다.

---

# 18. Lexer와 Parser의 역할 정리

전체 과정을 다시 정리하면 다음과 같습니다.

```text
                    Shell Input
                         │
                         ▼
                  ┌─────────────┐
                  │    Lexer    │
                  └─────────────┘
                         │
                         │ 문자열 분석
                         ▼
                 Token Linked List
                         │
                         ▼
                  ┌─────────────┐
                  │   Parser    │
                  └─────────────┘
                         │
                         │ 문법 분석
                         ▼
                    Command Tree
                         │
                         ▼
                    ┌─────────┐
                    │Executor │
                    └─────────┘
                         │
                         ▼
                    실제 명령 실행
```

각 단계의 책임을 정리하면 다음과 같습니다.

| 단계             | 역할                          |
| -------------- | --------------------------- |
| **Lexer**      | 입력 문자열을 Token으로 분리          |
| **Token List** | Lexer와 Parser 사이에서 Token 전달 |
| **Parser**     | Token들의 문법적 관계를 분석          |
| **LCRS Tree**  | 명령어의 계층적인 구조 표현             |
| **Executor**   | Tree를 기반으로 실제 명령 실행         |

---

# 19. 핵심 구현 포인트

이 프로젝트에서 Lexer와 Parser를 구현하면서 중요했던 부분은 다음과 같습니다.

### 1. Lexer와 Parser의 책임 분리

Lexer가 문법까지 해석하지 않고,

```text
문자열 → Token
```

만 담당하도록 했습니다.

Parser는 Token을 입력으로 받아

```text
Token → Tree
```

를 수행합니다.

---

### 2. Quote를 고려한 Word Parsing

단순한 공백 기준 분리가 아니라

```bash
echo "hello world"
```

와 같은 입력에서 `"hello world"`를 하나의 Word로 처리하도록 구현했습니다.

---

### 3. Operator의 종류 구분

다음과 같은 Shell Operator를 각각 구분합니다.

```text
|
||
&&
<
>
<<
>>
```

이를 통해 Parser가 이후 문법적인 의미를 구분할 수 있도록 했습니다.

---

### 4. Recursive Descent Parsing

Shell의 문법 구조를 Parser 함수의 호출 구조와 대응시켰습니다.

```text
parse_list()
    │
    ▼
parse_pipeline()
    │
    ▼
parse_command()
    │
    ▼
parse_simple_command()
```

따라서 문법의 계층 구조가 코드 구조에 직접적으로 반영됩니다.

---

### 5. LCRS를 이용한 Tree 구성

Shell의 문법은 하나의 노드가 여러 개의 자식을 가질 수 있기 때문에 `child_list`와 `next`를 이용한 LCRS 구조를 사용했습니다.

```text
Parent
  │
  ▼
Child 1 → Child 2 → Child 3
```

이를 통해 Command 내부의 여러 Word, Redirection 등의 관계를 Tree 형태로 표현할 수 있습니다.

---

# 20. 최종적으로 이해해야 할 구조

이 프로젝트의 Lexer와 Parser를 가장 간단하게 표현하면 다음과 같습니다.

```text
"echo hello | grep hello > result.txt"
                    │
                    ▼
                 Lexer
                    │
                    ▼
        ┌──────────────────────┐
        │ WORD echo            │
        │ WORD hello           │
        │ PIPE                 │
        │ WORD grep            │
        │ WORD hello           │
        │ REDIRECTION >        │
        │ WORD result.txt      │
        └──────────────────────┘
                    │
                    ▼
                 Parser
                    │
                    ▼
                  ROOT
                    │
                   LIST
                    │
                PIPELINE
                /       \
          COMMAND      COMMAND
             │            │
        SIMPLE_CMD    SIMPLE_CMD
        /       \      /    |     \
      echo     hello  grep hello  REDIRECTION
                                      │
                                   result.txt
                    │
                    ▼
                 Executor
                    │
                    ▼
                  실행
```

결국 **Lexer는 Shell 명령어를 "읽을 수 있는 단위"로 만들고, Parser는 그 단위들을 "실행할 수 있는 구조"로 변환하는 역할**을 합니다.

이 구조를 이해하면 이후 Executor에서 왜 Tree를 순회하면서 Pipe, Redirection, Command를 처리하는지도 자연스럽게 연결됩니다.
