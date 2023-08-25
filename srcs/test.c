#include "../includes/minishell.h"

void handler(int signum)
{
    if (signum != SIGINT)
        return ;
    write(STDOUT_FILENO, "\n", 1);
    if (rl_on_new_line() == -1)
        exit(1);
    rl_replace_line("", 1);
    rl_redisplay();
}

int main(void)
{
    char *line;

    signal(SIGINT, handler);
    while (1)
    {
        line = readline("minishell> ");
		add_history(line);
        if (line)
        {
            free(line);
            line = 0;
        }
        else
		{
			printf("exit");
            exit(1);
		}
    }
    return (0);
}