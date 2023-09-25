#include "../includes/minishell.h"

static char *make_str(char *cmd_line, int start, int end)
{
	char *new_str;
	int i;

	new_str = malloc(sizeof(char) * (end - start + 2));
	i = 0;
	while (start <= end)
	{
		new_str[i] = cmd_line[start];
		i++;
		start++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static s_str_info *make_and_init_str_info(char *cmd_line, int start, int end)
{
    int len_string;
    s_str_info *str_info;

    len_string = count_quote_string(cmd_line, start, end);
    str_info = malloc(sizeof(s_str_info) * (len_string + 1));
    if (str_info == 0)
        malloc_error();
    str_info[len_string].str = 0;
    str_info[len_string].str_len = 0;
    str_info[len_string].str_type = NUL;
    return (str_info);
}

s_str_info *make_quote_string(char *cmd_line, int start, int end)
{
	int len_string;
	int i;
    int j;
	s_str_info *str_info;

	i = 0;
	str_info = make_and_init_str_info(cmd_line, start, end);
	while (start < end)
	{
		if (check_is_single_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\''))
		{
			j = start + 1;
			single_close_quote(cmd_line, &start, end);
			str_info[i].str = make_str(cmd_line, j, start - 2);
			str_info[i].str_len = ft_strlen(str_info[i].str);
			str_info[i].str_type = SINGLE_QUOTE;
		}
		else if (check_is_double_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\"'))
		{
			j = start + 1;
			double_close_quote(cmd_line, &start, end);
			str_info[i].str = make_str(cmd_line, j, start - 2);
			str_info[i].str_len = ft_strlen(str_info[i].str);
			str_info[i].str_type = DOUBLE_QUOTE;
		}
		else
		{
			j = start;
			normal_string(cmd_line, &start, end);
			str_info[i].str = make_str(cmd_line, j, start - 1);
			str_info[i].str_len = ft_strlen(str_info[i].str);
			str_info[i].str_type = STRING;
		}
		i++;
	}
	return (str_info);
}
