#include "../includes/minishell.h"

void single_close_quote(char *cmd_line, int *start, int end)
{
    (*start)++;
    while (*start < end && !check_is_single_quote(cmd_line[*start]))
        (*start)++;
    (*start)++;
}

void double_close_quote(char *cmd_line, int *start, int end)
{
    (*start)++;
    while (*start < end && !check_is_double_quote(cmd_line[*start]))
        (*start)++;
    (*start)++;
}

void normal_string(char *cmd_line, int *start, int end)
{
    while (*start < end)
    {
        if (check_is_single_quote(cmd_line[*start]) \
        && check_is_close_quote(cmd_line, *start, '\''))
            break;
        if (check_is_double_quote(cmd_line[*start]) \
        && check_is_close_quote(cmd_line, *start, '\"'))
            break;
        (*start)++;
    }
}

int count_quote_string(char *cmd_line, int start, int end)
{
	int cnt_string;

	cnt_string = 0;
	while (start < end)
	{
		if (check_is_single_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\''))
            single_close_quote(cmd_line, &start, end);
		else if (check_is_double_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\"'))
            double_close_quote(cmd_line, &start, end);
		else
            normal_string(cmd_line, &start, end);
		cnt_string++;
	}
	return (cnt_string);
}
