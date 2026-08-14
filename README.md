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

## 핵심적으로 배울 수 있는 5가지

### 1. Process

```c
fork();
execve();
waitpid();
```

를 이용하면서 **프로세스가 어떻게 생성되고 프로그램이 어떻게 실행되는지** 이해하게 됩니다.

---

### 2. File Descriptor

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

### 3. IPC와 Pipe

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

### 4. Parser

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

### 5. Memory Management

# 4. 구현 범위 — 구현해야 하는 내용

Minishell의 구현 범위는 크게 **입력창 + 파싱 + 외부 명령 실행 + redirection + pipe + environment + signal + builtin**으로 나눌 수 있습니다.

---

## 4-1. Prompt 및 History

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

## 4-2. Parsing

[Lexer & Parser](docs/PARSE.md)

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

## 4-3. 외부 명령 실행

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

## 4-4. Quote

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

## 4-5. Environment Variable

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

## 4-6. Redirection

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

## 4-7. Pipe

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

## 4-8. Builtin

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

## 4-9. Signal

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

## 4-10. Memory Management

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

## 4-11. Bonus

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

경우 동일한 부분을 반복 탐색하여 최악의 경우 실행 시간이 크게 증가할 수 있습니다.**

다만 일반적인 Shell 사용에서는 Pattern과 파일명이 짧고 디렉터리의 파일 수도 제한적이기 때문에 실질적인 성능 문제가 발생할 가능성은 낮습니다.


---

### wildcard

[Wildcard](docs/WILDCARD.md)

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

