#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios term;
    
    // 터미널 설정 가져오기
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
        return 1;
    }

    // 입력을 즉시 사용 가능하도록 설정
    term.c_cc[VMIN] = 1;   // 최소 1 문자를 읽도록 설정
    term.c_cc[VTIME] = 0;  // 읽기 작업이 무한 대기하지 않도록 설정

    // 수정된 설정을 다시 적용
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        perror("tcsetattr");
        return 1;
    }

    printf("Enter a character: ");
    
    // 문자 하나를 바로 읽어들임
    char character;
    if (read(STDIN_FILENO, &character, 1) == -1) {
        perror("read");
        return 1;
    }

    printf("You entered: %c\n", character);

    return 0;
}