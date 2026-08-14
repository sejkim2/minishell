# Process, Pipe, FD

Minishell에서 명령어를 실제로 실행하기 위해서는 **Process, Pipe, File Descriptor(FD)**가 함께 사용됩니다.

세 개념은 서로 독립적으로 존재하는 것이 아니라 다음과 같은 관계를 가집니다.

```text
Process
  │
  ├── FD를 통해 입력과 출력을 관리
  │
  └── Pipe를 통해 다른 Process와 데이터 전달
```

즉,

* **Process**: 명령어를 실행하는 주체
* **Pipe**: Process와 Process 사이에 데이터를 전달하는 통로
* **FD(File Descriptor)**: Process가 파일이나 Pipe 등의 입출력 대상을 가리키는 번호

이 프로젝트에서는 이러한 기능들이 주로 `srcs/run_dir/`의 실행 로직에서 결합됩니다.

---

## 1. Process

### 1.1 Process란?

Process는 실행 중인 프로그램의 인스턴스입니다.

Minishell에서 사용자가 다음과 같은 명령어를 입력했다고 가정합니다.

```bash
ls -al
```

Minishell은 `ls`라는 프로그램을 실행하기 위해 새로운 Process를 생성하고, 해당 Process에서 `ls`를 실행합니다.

프로세스 생성에는 `fork()`가 사용되고, 외부 프로그램 실행에는 `execve()`가 사용됩니다.

전체적인 흐름은 다음과 같습니다.

```text
Minishell Process
      │
      │ fork()
      ▼
Child Process
      │
      │ execve()
      ▼
ls 실행
```

부모 Process는 Minishell 자체이고, 자식 Process는 실제 명령어를 실행하는 역할을 담당합니다.

---

### 1.2 fork()

`fork()`는 현재 Process를 복제하여 새로운 Process를 생성합니다.

```text
Parent Process
      │
      │ fork()
      ├───────────────┐
      ▼               ▼
Parent            Child
Minishell          command
```

`fork()` 이후에는 부모와 자식이 각각 실행을 계속합니다.

반환값을 이용하여 어느 Process에서 실행 중인지 구분할 수 있습니다.

```c
pid = fork();

if (pid == 0)
{
    // Child Process
}
else
{
    // Parent Process
}
```

Minishell에서는 자식 Process에서 명령어를 실행하고 부모 Process는 필요한 경우 자식의 종료를 기다립니다.

---

### 1.3 execve()

`fork()`가 Process를 생성하는 역할이라면 `execve()`는 해당 Process에서 실제 프로그램을 실행하는 역할을 합니다.

```text
fork()
  ↓
Child Process 생성
  ↓
execve()
  ↓
실제 프로그램 실행
```

예를 들어 다음 명령어를 실행하면

```bash
/bin/ls
```

자식 Process에서 `execve()`를 호출하여 `ls` 프로그램으로 실행 내용을 교체합니다.

중요한 점은 `execve()`가 새로운 Process를 만드는 함수가 아니라는 것입니다.

```text
fork()  → Process 생성
execve() → 해당 Process에서 다른 프로그램 실행
```

---

### 1.4 부모 Process와 자식 Process

Minishell은 명령어를 실행한 뒤 자식 Process의 종료 상태를 확인할 필요가 있습니다.

```text
Minishell
   │
   ├── fork()
   │
   ├── Child
   │     └── execve(command)
   │
   └── Parent
         └── wait()
```

이 과정을 통해 Minishell은 명령어가 정상적으로 종료되었는지 확인하고 `$?`와 같은 종료 상태에도 반영할 수 있습니다.

---

# 2. File Descriptor

## 2.1 FD란?

File Descriptor(FD)는 Process가 열어 놓은 파일이나 입출력 대상을 식별하는 정수입니다.

일반적으로 다음 세 개의 FD가 기본적으로 존재합니다.

|  FD | 이름     | 의미    |
| --: | ------ | ----- |
| `0` | stdin  | 표준 입력 |
| `1` | stdout | 표준 출력 |
| `2` | stderr | 표준 에러 |

```text
0 → stdin
1 → stdout
2 → stderr
```

예를 들어 일반적인 명령어 실행에서는

```text
keyboard
   │
   ▼
stdin (0)

command

stdout (1)
   │
   ▼
terminal
```

과 같은 구조를 가집니다.

---

## 2.2 Redirection과 FD

Shell에서 다음과 같은 명령어를 사용할 수 있습니다.

```bash
echo hello > result.txt
```

여기서 `>`는 stdout의 목적지를 터미널에서 파일로 변경합니다.

이를 FD 관점에서 보면

```text
기존

stdout (1)
   │
   ▼
terminal
```

에서

```text
변경 후

stdout (1)
   │
   ▼
result.txt
```

로 변경하는 것입니다.

이때 핵심적으로 사용되는 함수가 `dup2()`입니다.

---

## 2.3 dup2()

`dup2(oldfd, newfd)`는 `oldfd`가 가리키는 대상을 `newfd`가 가리키도록 연결합니다.

예를 들어

```c
fd = open("result.txt", ...);
dup2(fd, STDOUT_FILENO);
```

를 수행하면

```text
fd
 │
 ▼
result.txt

stdout (1)
 │
 └──────────► result.txt
```

가 됩니다.

따라서 이후 프로그램이

```c
write(1, ...);
```

또는 일반적인 `printf()`를 사용하면 출력이 터미널이 아니라 `result.txt`로 전달됩니다.

이것이 Shell의 redirection이 동작하는 핵심 원리입니다.

---

# 3. Pipe

## 3.1 Pipe란?

Pipe는 한 Process의 출력을 다른 Process의 입력으로 전달하기 위한 IPC(Inter-Process Communication) 방식입니다.

다음 명령어를 생각해 봅니다.

```bash
ls | grep txt
```

우리가 원하는 데이터 흐름은 다음과 같습니다.

```text
ls
 │
 │ stdout
 ▼
┌─────────┐
│  pipe   │
└─────────┘
     │
     │ stdin
     ▼
grep txt
```

즉,

```text
ls의 stdout
      ↓
    pipe
      ↓
grep의 stdin
```

으로 연결됩니다.

---

## 3.2 pipe()와 두 개의 FD

`pipe()`는 데이터를 전달할 수 있는 통로와 두 개의 FD를 생성합니다.

```text
pipefd[0] → read end
pipefd[1] → write end
```

즉,

```text
Process A
   │
   │ write
   ▼
pipefd[1]
   │
   │
   ▼
┌─────────┐
│   Pipe  │
└─────────┘
   │
   │
   ▼
pipefd[0]
   │
   │ read
   ▼
Process B
```

따라서 Pipe 자체가 Process는 아닙니다.

Pipe는 **Process 사이에서 데이터를 전달하는 통로**이고, 실제 연결은 FD를 통해 이루어집니다.

---

# 4. Process + Pipe + FD

세 개념의 관계를 이해하는 것이 Minishell의 실행 구조를 이해하는 핵심입니다.

다음 명령어를 예로 들어보겠습니다.

```bash
ls | grep txt
```

### 4.1 Process 생성

먼저 각각의 명령어를 실행할 Process가 필요합니다.

```text
Minishell
   │
   ├── fork() → Process A
   │              └── ls
   │
   └── fork() → Process B
                  └── grep txt
```

---

### 4.2 Pipe 생성

두 Process 사이에 데이터를 전달하기 위해 Pipe를 생성합니다.

```text
Process A
   │
   │ stdout
   ▼
pipe write
   │
   ▼
  PIPE
   │
   ▼
pipe read
   │
   │ stdin
   ▼
Process B
```

---

### 4.3 FD 연결

이제 `dup2()`를 이용하여 각 Process의 표준 입출력을 Pipe에 연결합니다.

첫 번째 Process:

```text
ls

stdout (1)
    │
    ▼
pipe write end
```

두 번째 Process:

```text
grep txt

stdin (0)
    │
    ▼
pipe read end
```

결과적으로

```text
       Process A                 Process B
          ls                    grep txt
           │                       ▲
       stdout(1)                stdin(0)
           │                       │
           ▼                       │
      pipe write ──── PIPE ──── pipe read
```

가 됩니다.

---

# 5. Pipeline에서의 실제 실행 흐름

Minishell의 `run_pipeline.c`는 Pipeline 실행을 담당합니다.

예를 들어

```bash
cat file.txt | grep hello | wc -l
```

과 같은 명령어를 생각할 수 있습니다.

이 경우 Process는 세 개가 필요합니다.

```text
Process 1          Process 2          Process 3
   cat                grep               wc
    │                  │                  │
 stdout              stdin              stdin
    │                  │                  │
    ▼                  ▲                  ▲
  Pipe 1 ──────────────┘                  │
                                           │
  Pipe 2 ─────────────────────────────────┘
```

보다 정확하게 표현하면 다음과 같습니다.

```text
cat
 │
 │ stdout
 ▼
Pipe 1
 │
 │ stdin
 ▼
grep
 │
 │ stdout
 ▼
Pipe 2
 │
 │ stdin
 ▼
wc
```

즉 Pipeline이 길어질수록 Process와 Pipe가 함께 증가합니다.

---

# 6. Pipe와 FD의 관계

Pipe를 이해할 때 가장 중요한 부분입니다.

`pipe()`는 단순히 "두 Process를 연결"하는 것이 아닙니다.

실제로는 **Pipe에 접근할 수 있는 두 개의 FD를 생성**합니다.

```text
pipe()
  │
  ├── pipefd[0] → read
  │
  └── pipefd[1] → write
```

그리고 `dup2()`를 이용해 Process의 표준 입출력에 연결합니다.

```text
Process A

stdout(1)
   │
   │ dup2(pipefd[1], 1)
   ▼
pipe write end
```

```text
Process B

stdin(0)
   │
   │ dup2(pipefd[0], 0)
   ▼
pipe read end
```

따라서 다음과 같은 관계가 만들어집니다.

```text
             Process A
                 │
              stdout
                FD 1
                 │
               dup2
                 │
                 ▼
          Pipe write FD
                 │
                 ▼
               PIPE
                 │
                 ▼
          Pipe read FD
                 │
               dup2
                 │
                 ▼
              stdin
                FD 0
                 │
                 ▼
             Process B
```

---

# 7. Redirection과 Pipe가 함께 사용되는 경우

실제 Shell에서는 Pipe와 Redirection을 함께 사용할 수 있습니다.

```bash
cat file.txt | grep hello > result.txt
```

실행 구조는 다음과 같습니다.

```text
Process 1                         Process 2

cat                               grep hello
 │                                    │
 │ stdout                             │ stdout
 │                                    │
 ▼                                    ▼
Pipe write                        result.txt
 │
 ▼
 PIPE
 │
 ▼
Pipe read
 │
 │
 ▼
stdin
```

여기서는 FD가 두 가지 역할을 합니다.

### Process 1

```text
stdout → Pipe
```

### Process 2

```text
stdin  ← Pipe
stdout → result.txt
```

즉 하나의 Pipeline 안에서도 각 Process의 FD가 서로 다른 대상으로 연결될 수 있습니다.

---

# 8. 파일별 역할

`run_dir`에서는 Process, Pipe, FD와 관련된 실행 로직이 여러 파일로 나누어져 있습니다.

| 파일                     | 주요 역할                            |
| ---------------------- | -------------------------------- |
| `run_command.c`        | command/subshell 실행 및 Process 생성 |
| `run_simple_command.c` | 단일 명령어 실행                        |
| `run_exe.c`            | 외부 실행 파일 실행                      |
| `run_pipeline.c`       | Pipeline 및 Pipe 처리               |
| `run_redir.c`          | Redirection 및 FD 연결              |
| `run_redir_utils.c`    | Redirection 보조 처리                |
| `run_list.c`           | 명령어 실행 흐름 관리                     |
| `run_root.c`           | 전체 실행 과정의 진입점                    |

즉 `run_dir`의 실행 구조를 크게 나누면 다음과 같습니다.

```text
                    run_root
                       │
                       ▼
                    run_list
                       │
                       ▼
                  run_command
                       │
          ┌────────────┼────────────┐
          ▼            ▼            ▼
       Command      Pipeline     Redirection
          │            │            │
          ▼            ▼            ▼
       Process        Pipe          FD
          │            │            │
          └────────────┴────────────┘
                       │
                       ▼
                    execve()
```

---

# 9. 세 개념의 핵심 정리

| 개념      | 역할               | 주요 시스템 콜                       |
| ------- | ---------------- | ------------------------------ |
| Process | 명령어를 실행하는 주체     | `fork()`, `execve()`, `wait()` |
| Pipe    | Process 간 데이터 전달 | `pipe()`                       |
| FD      | 입출력 대상을 가리키는 식별자 | `open()`, `dup2()`, `close()`  |

세 개념의 관계는 다음 한 문장으로 정리할 수 있습니다.

> **Process가 명령어를 실행하고, Pipe가 Process 사이의 데이터 전달 통로를 만들며, FD가 Process의 stdin/stdout을 Pipe나 파일에 연결합니다.**

예를 들어

```bash
ls | grep txt > result.txt
```

는 다음과 같이 해석할 수 있습니다.

```text
                  Minishell
                     │
              Process 생성
                     │
          ┌──────────┴──────────┐
          ▼                     ▼
       Process 1             Process 2
          ls                  grep txt
          │                     │
      stdout(1)              stdin(0)
          │                     │
          ▼                     │
      Pipe write                │
          │                     │
          ▼                     │
         PIPE                   │
          │                     │
          ▼                     │
       Pipe read ───────────────┘
                                │
                            stdout(1)
                                │
                              dup2
                                │
                                ▼
                           result.txt
```

결국 **Process는 실행**, **Pipe는 전달**, **FD는 연결**을 담당한다고 이해하면 됩니다.

이 세 가지를 함께 이해하면 `run_dir`에서 `fork()`, `pipe()`, `dup2()`, `execve()`, `wait()`가 왜 필요한지 자연스럽게 연결됩니다.
