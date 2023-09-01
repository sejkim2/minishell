#include "../includes/minishell.h"

int main(void)
{
    char *line;

    while (1)
    {
        line = readline("minishell> ");
        if (line)
        {
            add_history(line);
            // tokenize(line);
            free(line);
            line = 0;
        }
        else
            exit(1);
    }
    return (0);
}
