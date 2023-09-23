#include "../includes/minishell.h"

int check_is_close_quote(char *cmd_line, int index, char quote)
{
    index++;
    while (cmd_line[index])
    {
        if (cmd_line[index] == quote)
            break;
        index++;
    }
    if (cmd_line[index] == quote)
        return (1);
    else
        return (0);
}