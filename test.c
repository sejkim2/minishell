#include <stdio.h>
#include <stdlib.h>

void ff()
{
    system("leaks a.out");
}

void f()
{
    exit(1);
    char *c = malloc(sizeof(char) * 3);
    c[0] = 'a';
    printf("[%c]", c[0]);
}

int main(void)
{
    atexit(ff);
    char *c = malloc(sizeof(char) * 3);
    c[0] = 'a';
    printf("[%c]", c[0]);
    // exit(1);
    // f();
    // exit(1);
}