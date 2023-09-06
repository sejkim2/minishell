#include <stdio.h>
#include <term.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/ioctl.h>

int main()
{
    struct termios term;

    int tmp = tcgetattr(STDIN_FILENO, &term);
    
}
