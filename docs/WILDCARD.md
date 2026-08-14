
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

> **현재 디렉터리의 모든 파일을 순회하기 때문에 파일 수가 많을수록 탐색 비용이 증가하며, `*`를 처리하는 과정에서 Recursive Backtracking을 사용하기 때문에 여러 개의 `*`, 반복되는 문자, 긴 파일명, 마지막에서의 Pattern 불일치가 결합된 
