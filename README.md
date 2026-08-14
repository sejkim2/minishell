# 1. 프로젝트 개요

## Minishell이란?

**Minishell은 Unix Shell의 동작 원리를 직접 구현하는 42 Seoul의 시스템 프로그래밍 프로젝트** 입니다.

터미널에서 다음과 같이 명령을 입력하면:

```bash
$ ls -al
$ cd ..
$ cat file.txt | grep hello
$ echo "hello $USER"
```

Shell은 단순히 명령어를 실행하는 것이 아니라 다음 작업을 수행합니다.

```text
사용자 입력
    ↓
명령어 해석
    ↓
환경변수 / quote / redirection 처리
    ↓
프로세스 생성
    ↓
pipe / file descriptor 연결
    ↓
프로그램 실행
    ↓
프로세스 종료 대기
    ↓
exit status 저장
    ↓
다음 명령 대기
```

Minishell에서는 이 과정을 **C와 Unix 시스템 콜을 이용하여 직접 구현** 합니다.

즉, 프로젝트의 본질은

> **"bash의 일부 기능을 직접 구현하면서 Unix의 프로세스와 파일 입출력 시스템을 이해하는 것"**

이라고 볼 수 있습니다.

---

# 2. 실제 Shell이란?

## Shell의 정의

Shell은 쉽게 말하면:

> **사용자의 명령을 해석하고 운영체제에게 프로그램 실행을 요청하는 프로그램**

입니다.

대표적인 Shell은:

- `bash`
- `zsh`
- `fish`

등이다.

터미널에서:

```bash
$ ls
```

라는 명령을 입력하면 실제로는 다음과 같은 과정을 거칩니다.

```text
사용자
  │
  │ "ls -al"
  ▼
Shell
  │
  ├─ Lexer에서 "ls -al"라는 명령을 ["ls" "-al"]으로 토큰화
  ├─ Parser
  ├─ Command Tree
  ├─ PATH에서 ls 검색
  ├─ 프로세스 생성
  ├─ ls 실행
  └─ 종료 대기
  │
  ▼
다시 prompt
```

---

## Shell과 프로그램의 관계

중요한 점은 **Shell 자체가 `ls`, `cat`, `grep` 등을 구현하고 있는 것이 아니라는 것** 입니다.

예를 들어:

```bash
ls
```

를 입력하면 Shell은 대략:

```text
Shell
 │
 └─ fork()
      │
      ▼
    Child
      │
      └─ execve("/bin/ls", ...)
                     │
                     ▼
                    ls
```

와 같이 동작합니다.

즉:

> **Shell은 다른 프로그램을 실행시키는 프로그램 입니다.**

Shell은 크게 다음 세 가지 역할로 생각할 수 있습니다.

                    Shell
                      │
          ┌───────────┼───────────┐
          │           │           │
        해석         실행         제어
          │           │           │
        Parser      fork        Signal
        Quote       execve      wait
        $변수       pipe
        redir       builtin

이 프로젝트에서는 이러한 역할을 기능별 디렉터리로 분리했습니다.

```text
srcs/
├── builtin_dir
├── env_dir
├── heredoc_dir
├── lexer_dir
├── parser_dir
├── run_dir
├── signal_dir
└── wild_card_dir
```

따라서 디렉터리 구조 자체가 Shell의 주요 구성 요소를 보여줍니다.

---


## 프로젝트의 기본 실행 모습

완성된 Minishell은 대략 다음과 같이 동작합니다.

[이미지]

사용자가 명령을 입력하면 Minishell이 이를 해석하고 실행한 뒤 다시 prompt를 출력합니다.

---

# 3. 이 프로젝트에서 배울 수 있는 개념들

Minishell의 가장 큰 특징은 **여러 운영체제 개념이 하나의 프로젝트 안에서 연결된다는 것** 입니다.

| 개념 | Minishell에서 배우는 내용 |
| --- | --- |
| Process | 프로세스의 생성과 종료 |
| `fork()` | 부모/자식 프로세스 생성 |
| `execve()` | 프로세스에서 다른 프로그램 실행 |
| `waitpid()` | 자식 프로세스 종료 대기 |
| File Descriptor | stdin/stdout/stderr 관리 |
| `dup2()` | 입출력 방향 변경 |
| `pipe()` | 프로세스 간 데이터 전달 |
| Signal | `Ctrl-C`, `Ctrl-\` 등 처리 |
| Environment | 환경변수 관리 |
| Redirection | 파일과 stdin/stdout 연결 |
| Parsing | 사용자 입력 해석 |
| Expansion | `$USER`, `$PATH`, `$?` 등의 처리 |
| Builtin | Shell 내부 명령어 구현 |
| Memory Management | 동적 메모리와 메모리 누수 관리 |
| Process synchronization | 부모/자식 프로세스 실행 순서 관리 |

예를 들어:

```bash
cat file.txt | grep hello > result.txt
```

하나를 실행하기 위해서도

```text
Parser
  ↓
Pipe
  ↓
fork()
  ↓
dup2()
  ↓
Redirection
  ↓
execve()
  ↓
waitpid()
```

가 모두 연결됩니다.

---

## 핵심적으로 배울 수 있는 4가지

### ① Process

```c
fork();
execve();
waitpid();
```

를 이용하면서 **프로세스가 어떻게 생성되고 프로그램이 어떻게 실행되는지** 이해하게 됩니다.

---

### ② File Descriptor

Unix에서:

```text
0 → stdin
1 → stdout
2 → stderr
```

라는 개념을 직접 사용하게 됩니다.

그리고:

```c
open();
close();
dup();
dup2();
```

를 통해 파일 디스크립터를 직접 관리합니다.

---

### ③ IPC와 Pipe

```bash
ls | grep txt
```

를 구현하면서:

```text
프로세스 A
  stdout
    ↓
  pipe
    ↓
프로세스 B
  stdin
```

이라는 **프로세스 간 통신(IPC)** 구조를 이해하게 됩니다.

---

### ④ Parser

Shell은 입력 문자열을 단순히 공백 기준으로 자르면 안 됩니다.

예를 들어:

```bash
echo "hello world"
```

와

```bash
echo '$USER'
```

와

```bash
echo "$USER"
```

는 서로 다르게 해석되어야 합니다.

따라서 **Lexer → Parser → Executor**라는 구조를 직접 설계하게 되었습니다.

특히 이 프로젝트에서는 Parser의 결과를 단순한 배열이 아니라 Tree 구조로 표현합니다.

minishell.h 에는 다음과 같은 Symbol이 정의되어 있습니다.

```c
ROOT
LIST
SUBSHELL
PIPELINE
COMMAND
SIMPLE_COMMAND
PIPE
AND_IF
OR_IF
REDIRECTION
```

그리고 t_tree_node를 이용해 명령어 실행 구조를 구성합니다.

따라서 전체적인 자료구조 흐름은 다음과 같습니다.

```text
Token Linked List
    ↓
  Parser
    ↓
  Tree
    ↓
Execution
```

---

# 4. 구현 범위 — 구현해야 하는 내용

Minishell의 구현 범위는 크게 **명령어 해석 + Shell 기본 기능 + 명령 실행 + redirection + pipe + environment + signal + builtin**으로 나눌 수 있습니다.

---

## 4-1. 기본 Shell

### Prompt 및 History

main.c에서 readline()을 이용해 사용자 입력을 받고, 입력된 명령을 처리한 후 다시 Prompt를 출력하는 REPL 구조를 사용합니다.

```text
┌────────────────────┐
│ readline()         │
│       ↓            │
│ lexer()            │
│       ↓            │
│ parser()           │
│       ↓            │
│ run_root()         │
│       ↓            │
│ free               │
└─────────┬──────────┘
          │
          └── 다시 readline()
```

입력된 명령은 History에도 추가합니다.

readline("minishell$ ");
add_history();

이전에 입력했던 명령을 history에서 다시 사용할 수 있어야 합니다.

예를 들어:

```text
↑
↓
```

등으로 이전 명령을 탐색할 수 있습니다.

`readline()`과 `add_history()`를 사용합니다.

---

# 4-2. Lexer

Lexer는 단순히 공백을 기준으로 문자열을 분리하는 방식이 아닙니다.

다음과 같은 Token 종류를 정의하고 있습니다.

```text
WORD
REDIRECTION
PIPE
AND_IF
OR_IF
L_BRA
R_BRA
...
```

Lexer 디렉터리는 다음과 같이 구성되어 있습니다.

```text
srcs/lexer_dir/
├── lexer.c
├── tokenize.c
├── parse_redirection.c
├── parse_quote_string.c
├── parse_pipe_or_orif_or_andif.c
├── parse_word_or_branket.c
└── ...
```

따라서 다음과 같은 문법을 구분할 수 있습니다.

```text
echo hello
echo "hello world"
cat < input.txt
cat << EOF
ls | grep txt
echo A && echo B
echo A || echo B
```

또한 (, )도 Token으로 처리하며, 괄호의 짝과 잘못된 괄호 구조를 검사합니다.

# 4-3. Parser

Parser는 Lexer가 만든 Token Linked List를 Tree 구조로 변환합니다.

전체적인 흐름은 다음과 같습니다.

```text
Token Linked List
        ↓
      parser()
        ↓
    parse_list()
        ↓
      Tree
```

예를 들어 다음 명령어는

```
cat file | grep hello > result.txt
```

Lexer에서는 다음과 같은 Token이 만들어집니다.

```
WORD
WORD
PIPE
WORD
WORD
REDIRECTION
WORD
```

Parser는 이를 Tree 구조로 변환합니다.

개념적으로 다음과 같은 구조가 됩니다.

```text
              ROOT
                │
               LIST
                │
             PIPELINE
             /      \
          cat       grep
           │          │
         file        hello
                       │
                       ↓
                  result.txt
```

이렇게 만들어진 Tree를 Executor가 순회하면서 실제 명령을 실행합니다.

# 4-4. Tree

이 프로젝트의 핵심적인 특징 중 하나는 Tree 기반의 실행 구조입니다.

Header에서는 다음과 같은 t_tree_node를 사용합니다.

```
typedef struct s_tree_node
{
    int in_fork;
    t_symbol symbol;
    t_token *token;
    int num_of_child;
    struct s_tree_node *next;
    struct s_tree_node *child_list;
} t_tree_node;
```

실행의 진입점은 run_root()입니다.

전체 실행 흐름은 다음과 같습니다.

```text
main
 ↓
lexer
 ↓
parser
 ↓
Tree
 ↓
run_root
 ↓
run_list
 ↓
run_pipeline
 ↓
run_command
 ↓
builtin / execve
```

즉 Parser는 실행할 명령의 구조를 만드는 역할을 담당하고, run_* 계열의 함수는 만들어진 Tree를 실제 프로세스 실행으로 연결합니다.

# 4-2. 외부 명령 실행

다음과 같은 명령을 실행할 수 있어야 합니다.

```bash
ls
cat
grep
wc
```

그리고 실행 파일을 찾을 때:

### PATH

```bash
ls
```

→ `PATH`를 검색

### 절대 경로

```bash
/bin/ls
```

→ 해당 경로 직접 실행

### 상대 경로

```bash
./a.out
```

→ 해당 경로 직접 실행

이를 위해 주로:

```c
fork()
execve()
waitpid()
```

등을 사용합니다.

---

# 4-3. Quote

### Single Quote

```bash
echo '$USER'
```

→ `$USER`를 해석하지 않습니다.

결과:

```text
$USER
```

---

### Double Quote

```bash
echo "$USER"
```

→ `$USER`는 해석합니다.

즉:

```text
'...' → 내부 내용을 거의 그대로 취급

"..." → 대부분 그대로 취급하지만 $는 해석
```

이라는 규칙을 구현해야 합니다.

---

# 4-4. Environment Variable

환경변수 expansion을 지원합니다.

```bash
echo $USER
echo $HOME
echo $PATH
```

또한:

```bash
echo $?
```

를 통해 **직전에 실행된 foreground pipeline의 종료 상태**를 가져올 수 있어야 합니다.

예:

```bash
false
echo $?
```

결과:

```text
1
```

---

# 4-5. Redirection

네 가지 redirection을 구현합니다.

```text
<
>
<<
>>
```

### `<`

```bash
cat < input.txt
```

```text
input.txt
    ↓
  stdin
    ↓
  cat
```

---

### `>`

```bash
echo hello > result.txt
```

```text
echo
 ↓
stdout
 ↓
result.txt
```

기존 파일 내용은 덮어씁니다.

---

### `>>`

```bash
echo hello >> result.txt
```

기존 내용 뒤에 추가합니다.

---

### `<<`

Heredoc

```bash
cat << EOF
hello
world
EOF
```

`EOF`가 delimiter가 되고, 해당 delimiter가 나올 때까지 입력을 받습니다.

---

# 4-6. Pipe

```bash
ls | grep txt
```

를 구현해야 합니다.

구조는:

```text
        pipe
      ┌─────────┐
      │         │
      ▼         │
     ls ───────> grep
    stdout      stdin
```

입니다.

여러 개도 가능합니다.

```bash
cat file | grep hello | wc -l
```

```text
cat
 │
 ▼
pipe
 │
 ▼
grep
 │
 ▼
pipe
 │
 ▼
wc
```

---

# 4-7. Builtin

Shell 내부에서 직접 구현해야 하는 명령어가 있습니다.

```text
echo
cd
pwd
export
unset
env
exit
```

각각:

```bash
echo hello

cd ..

pwd

export NAME=sejin

unset NAME

env

exit
```

등을 처리해야 합니다.

특히 **`cd`가 중요한 예외** 입니다.

`cd`는 현재 Shell의 working directory 자체를 변경해야 하기 때문에 단순히 child process에서 실행하면 안 됩니다.

```text
Shell
 │
 ├─ cd 실행
 │
 └─ working directory 변경
```

이라는 구조가 필요합니다.

---

# 4-8. Signal

다음 세 가지를 처리해야 합니다.

```text
Ctrl-C
Ctrl-D
Ctrl-\
```

interactive mode에서:

```text
Ctrl-C
→ 새로운 prompt

Ctrl-D
→ shell 종료

Ctrl-\
→ 아무 동작 없음
```

이 되도록 해야 합니다.

또한 global variable은 최대 하나만 사용할 수 있으며, 이 변수는 **받은 signal 번호만 저장**해야 합니다.

---

# 4-9. Memory Management

모든 heap memory는 적절하게 해제해야 합니다.

특히 Minishell은 문자열과 token, command 구조체 등이 계속 생성되기 때문에:

```text
readline
 ↓
token
 ↓
parser
 ↓
command
 ↓
execution
```

과정에서 발생한 메모리를 정확히 관리해야 합니다.

`readline()` 자체에서 발생하는 특정 leak은 subject에서 예외로 인정하지만, **직접 작성한 코드의 memory leak은 허용되지 않습니다.**

---

# 4-10. Bonus

Bonus에서는 추가적으로:

```text
&&
||
()
*
```

를 구현합니다.

### `&&`

```bash
echo hello && echo world
```

첫 번째 명령이 성공해야 두 번째 명령을 실행합니다.

### `||`

```bash
false || echo hello
```

첫 번째 명령이 실패하면 두 번째 명령을 실행합니다.

### Parentheses

```bash
(echo A && echo B) || echo C
```

처럼 우선순위를 처리해야 합니다.

이 부분은 **AST(Abstract Syntax Tree)**를 사용하면 구현하기 좋습니다.

### Wildcard

Wildcard Expansion은 패턴을 만족하는 모든 파일을 찾아 실제 명령어의 인자로 확장하는 과정입니다.

예를 들어 현재 디렉터리가 다음과 같다고 가정하겠습니다.

```text
a.txt
b.txt
c.c
d.txt
README.md
```

다음 명령어를 입력하면:

```bash
ls *.txt
```

Shell은 `*.txt`를 그대로 `ls`에 전달하는 것이 아니라:

```text
*.txt
   ↓
a.txt
b.txt
d.txt
```

와 같이 확장합니다.

따라서 실제 실행은 개념적으로 다음과 같습니다.

```bash
ls a.txt b.txt d.txt
```

즉, Wildcard의 역할은 파일을 직접 처리하는 것이 아니라 **패턴에 일치하는 파일명을 찾아 명령어의 인자로 확장하는 것**입니다.

---

## 구현 흐름

구현에서는 `readdir()`을 이용하여 현재 디렉터리의 파일을 순회하면서 각각의 파일명이 Wildcard Pattern을 만족하는지 검사합니다.

```text
사용자 입력
    │
    ▼
Wildcard Pattern
    │
    ▼
opendir(".")
    │
    ▼
readdir()
    │
    ├── 파일 1 → Pattern Matching
    ├── 파일 2 → Pattern Matching
    ├── 파일 3 → Pattern Matching
    ├── ...
    └── 파일 N → Pattern Matching
    │
    ▼
일치 여부 저장
    │
    ▼
일치하는 파일 수집
    │
    ▼
char ** 배열 생성
    │
    ▼
Command의 Argument로 전달
```

---

## Pattern Matching 알고리즘

Wildcard Pattern Matching은 **재귀적인 Backtracking 방식**으로 구현했습니다.

일반적인 문자는 파일명의 문자와 1:1로 비교합니다.

```text
Pattern : abc*
File    : abcdef.txt

a == a
b == b
c == c
```

`*`를 만나면 `*`가 파일명의 어느 부분까지 소비해야 하는지 여러 후보를 탐색합니다.

예를 들어:

```text
Pattern : a*c
File    : abbbbbc
```

라면 `*`가 다음과 같은 여러 문자열을 소비할 수 있습니다.

```text
*
├── ""
├── "b"
├── "bb"
├── "bbb"
├── "bbbb"
└── "bbbbb"
```

각 후보에 대해 `*` 뒤에 남아 있는 Pattern이 파일명과 일치하는지 재귀적으로 검사합니다.

```text
일반 문자
    ↓
문자 단위 비교

*
    ↓
여러 매칭 위치 탐색
    ↓
뒤쪽 Pattern 재귀 검사
    ↓
성공 → Match
실패 → 다른 위치 탐색
```

따라서 이 구현은 **Wildcard Pattern Matching을 Recursive Backtracking으로 해결하는 방식**이라고 설명할 수 있습니다.

---

## Bit Mask를 이용한 파일 수집

Pattern Matching 결과는 바로 문자열 배열에 넣지 않고 `bit_mask`에 저장합니다.

예를 들어 현재 디렉터리가 다음과 같고:

```text
a.c
b.c
main.c
hello.txt
README
```

`*.c`에 대한 Matching 결과는 다음과 같이 저장됩니다.

```text
파일           bit_mask
-----------------------
a.c                1
b.c                1
main.c             1
hello.txt          0
README             0
```

이후 일치하는 파일만 다시 수집하여 최종 `char **` 배열로 변환합니다.

```text
Directory
    │
    ▼
Pattern Matching
    │
    ▼
bit_mask
    │
    ├── a.c       → 1
    ├── b.c       → 1
    ├── main.c    → 1
    ├── hello.txt → 0
    └── README    → 0
    │
    ▼
Matching Files
    │
    ▼
char **
```

---

## Hidden File 처리

Shell의 Wildcard 동작에 맞게 `.`으로 시작하는 숨김 파일도 별도로 처리합니다.

일반적인:

```bash
*
```

패턴에서는:

```text
.git
.env
.hidden
```

과 같은 숨김 파일을 기본적으로 매칭하지 않습니다.

반면 Pattern 자체가 `.`으로 시작한다면 숨김 파일을 대상으로 매칭할 수 있습니다.

```bash
.*
```

따라서 개념적으로 다음과 같이 동작합니다.

```text
*   → 일반 파일
.*  → 숨김 파일
```

---

# Wildcard의 성능

이 구현은 일반적인 사용에서는 충분히 빠르게 동작하지만, 특정 입력에서는 탐색 비용이 크게 증가할 가능성이 있습니다.

성능에 영향을 주는 요소는 크게 두 가지입니다.

### 1. 디렉터리의 파일 개수

Wildcard가 존재하면 현재 디렉터리의 파일들을 `readdir()`로 순회하면서 각각 Pattern Matching을 수행합니다.

따라서 파일 개수를 `N`이라고 하면 최소한:

```text
O(N)
```

의 파일 탐색 비용이 발생합니다.

예를 들어:

```text
파일 100개
→ 100개 검사

파일 10,000개
→ 10,000개 검사

파일 1,000,000개
→ 1,000,000개 검사
```

와 같이 디렉터리에 파일이 많아질수록 Wildcard Expansion 자체의 비용도 증가합니다.

또한 현재 구현에서는 Matching 결과를 `bit_mask`에 기록한 뒤 일치하는 파일을 다시 수집하기 때문에, 디렉터리 엔트리를 두 번 순회하는 비용도 발생합니다.

```text
첫 번째 순회
    ↓
Pattern Matching
    ↓
bit_mask 기록
    ↓
두 번째 순회
    ↓
일치하는 파일 수집
```

---

### 2. Backtracking으로 인한 중복 탐색

Pattern Matching에서 더 중요한 성능상의 특징은 `*`를 처리할 때 Backtracking을 사용한다는 점입니다.

예를 들어:

```text
Pattern : *a*a*a*b
File    : aaaaaaaaaaaaaaaaaaac
```

처럼 `*`가 여러 개이고 파일명에 반복되는 문자가 많으면 각 `*`가 어느 위치까지 문자열을 소비할지 여러 후보가 생깁니다.

```text
*a*a*a*b
 ↑
 ├── ""
 ├── "a"
 ├── "aa"
 ├── "aaa"
 └── ...
```

첫 번째 선택이 실패하면 다른 선택을 시도하고, 그 과정에서 뒤쪽 Pattern을 다시 검사합니다.

이러한 과정이 여러 `*`에 대해 반복될 수 있습니다.

특히 다음 조건이 동시에 존재하면 탐색량이 크게 증가할 수 있습니다.

```text
여러 개의 *
      +
반복되는 문자
      +
긴 파일명
      +
마지막 부분에서 Pattern 불일치
```

예를 들어:

```text
Pattern : *a*a*a*b
File    : aaaaaaaaaaaaaaaaaaac
```

에서는 앞부분이 여러 방식으로 매칭될 수 있지만 마지막의:

```text
b != c
```

에서 실패하기 때문에 앞에서 시도했던 여러 경우를 다시 탐색하게 됩니다.

---

## 시간 복잡도 관점

전체 Wildcard Expansion의 비용은 크게 다음 두 부분으로 생각할 수 있습니다.

```text
전체 비용
    =
디렉터리 탐색 비용
    +
Pattern Matching 비용
```

파일 개수를 `N`이라고 하면:

```text
O(N × Pattern Matching 비용)
```

으로 볼 수 있습니다.

일반적인 단순 Pattern에서는 파일명과 Pattern의 길이에 비례하는 수준으로 동작하지만, 현재 구현은 Backtracking을 사용하기 때문에 `*`가 여러 개 존재하는 특정 입력에서는 동일한 부분을 반복적으로 탐색할 수 있습니다.

따라서 **모든 입력에서 항상 동일한 복잡도를 갖는 것은 아니며, 최악의 경우 탐색량이 크게 증가할 수 있습니다.**

---

## 성능상 가장 불리한 입력

다음과 같은 조건에서 성능 문제가 발생할 가능성이 가장 높습니다.

| 조건                          | 영향                 |
| --------------------------- | ------------------ |
| `*`가 적음                     | 탐색량이 적음            |
| `*`가 많음                     | 탐색량 증가 가능          |
| 파일명이 짧음                     | 영향 적음              |
| 파일명이 김                      | 탐색량 증가 가능          |
| 반복되는 문자가 많음                 | Backtracking 증가 가능 |
| Pattern과 파일명이 여러 방식으로 매칭 가능 | Backtracking 증가    |
| 마지막에서 Pattern이 불일치          | 많은 후보를 끝까지 탐색할 가능성 |
| 디렉터리의 파일 수가 많음              | 전체 비용 증가           |

특히 다음 조건이 모두 결합된 경우 가장 불리합니다.

```text
여러 개의 *
+
반복되는 문자
+
긴 파일명
+
마지막에서 불일치
+
많은 파일
```

---

## 성능 개선 방법

현재 구현은 재귀적인 Backtracking을 사용하기 때문에 동일한 `(Pattern 위치, File 위치)` 상태를 여러 번 계산할 가능성이 있습니다.

이를 개선하는 대표적인 방법은 **Memoization 또는 Dynamic Programming**입니다.

현재 방식:

```text
(Pattern 위치, File 위치)
        ↓
      재귀
        ↓
같은 상태를 다시 계산할 수 있음
```

Memoization을 적용하면:

```text
(Pattern 위치, File 위치)
        ↓
이미 계산했는가?
   ├── Yes → 저장된 결과 재사용
   └── No  → 계산 후 결과 저장
```

하여 동일한 부분 문제의 반복 계산을 방지할 수 있습니다.

또한 `*`의 위치를 기억하면서 탐색하는 Greedy 기반의 Pattern Matching 알고리즘을 사용하여 Backtracking을 줄이는 방법도 있습니다.

---

## 결론

현재 구현의 Wildcard Expansion은 다음과 같은 구조를 가집니다.

```text
readdir()
    ↓
현재 디렉터리의 모든 파일 탐색
    ↓
각 파일에 대해
Recursive Backtracking Pattern Matching
    ↓
bit_mask에 Matching 결과 저장
    ↓
일치하는 파일 수집
    ↓
Command Argument로 확장
```

따라서 이 구현의 성능상 특징은 다음과 같이 정리할 수 있습니다.

> **현재 디렉터리의 모든 파일을 순회하기 때문에 파일 수가 많을수록 탐색 비용이 증가하며, `*`를 처리하는 과정에서 Recursive Backtracking을 사용하기 때문에 여러 개의 `*`, 반복되는 문자, 긴 파일명, 마지막에서의 Pattern 불일치가 결합된 경우 동일한 부분을 반복 탐색하여 최악의 경우 실행 시간이 크게 증가할 수 있습니다.**

다만 일반적인 Shell 사용에서는 Pattern과 파일명이 짧고 디렉터리의 파일 수도 제한적이기 때문에 실질적인 성능 문제가 발생할 가능성은 낮습니다.


---

# 5. 사용된 기술

Minishell에서 사용하는 기술을 크게 보면 다음과 같습니다.

## ① C

프로젝트 전체가 C로 작성됩니다.

```text
C
├── Pointer
├── Struct
├── Dynamic Memory
├── String
└── Function Pointer 등
```

기본적인 C 역량이 필요합니다.

---

## ② Unix System Call

Minishell의 핵심입니다.

### Process

```c
fork()
execve()
wait()
waitpid()
wait3()
wait4()
exit()
```

### File

```c
open()
read()
write()
close()
unlink()
```

### File Descriptor

```c
dup()
dup2()
```

### Pipe

```c
pipe()
```

### Directory

```c
opendir()
readdir()
closedir()
```

### Environment

```c
getenv()
```

### Directory 이동

```c
getcwd()
chdir()
```

---

## ③ Signal

```c
signal()
sigaction()
sigemptyset()
sigaddset()
kill()
```

특히 Shell과 child process에서 signal의 동작이 다르기 때문에 **signal handling 설계가 중요합니다.**

---


# 전체적으로 정리하면

Minishell을 하나의 흐름으로 보면 다음과 같습니다.

```text
                  Minishell
                     │
                     ▼
                readline()
                     │
                     ▼
                   Lexer
                     │
                     ▼
                   Parser
                     │
                     ▼
                 Expansion
                     │
                     ▼
                 Executor
                     │
           ┌─────────┼─────────┐
           │         │         │
        Builtin  Redirection  Pipe
           │         │         │
           └─────────┼─────────┘
                     ▼
                fork / execve
                     │
                     ▼
                  waitpid()
                     │
                     ▼
                exit status
                     │
                     ▼
                다음 prompt
```

