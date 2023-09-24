/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:40:01 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/22 15:03:11 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_symbol	parse_redirection(char *cmd_line, int *end, s_str_info **str_info)
{
	int start;

	while (cmd_line[*end] && check_is_white_space(cmd_line[*end]))
		(*end)++;
	if (!cmd_line[*end])
		print_unexpected_token_syntax_error('\n');
	if (cmd_line[*end] == '(' || cmd_line[*end] == ')' \
	|| cmd_line[*end] == '<' || cmd_line[*end] == '>' \
	|| cmd_line[*end] == '&' || cmd_line[*end] == '|')
		print_unexpected_token_syntax_error(cmd_line[*end]);
	start = *end;
	while (cmd_line[*end])
	{
		if (check_is_single_quote(cmd_line[*end]))
			parse_single_quote_string(cmd_line, end);
		else if (check_is_double_quote(cmd_line[*end]))
			parse_double_quote_string(cmd_line, end);
		else if (check_is_seperator(cmd_line[*end]))
			break ;
		else
			(*end)++;
	}
	*str_info = make_quote_string(cmd_line, start, *end);
	return (REDIRECTION);
}

char *make_str(char *cmd_line, int start, int end)
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

int count_quote_string(char *cmd_line, int start, int end)
{
	int cnt_string;

	cnt_string = 0;
	while (start < end)
	{
		if (check_is_single_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\''))
		{
			start++;
			while (start < end && !check_is_single_quote(cmd_line[start]))
				start++;
			start++;
		}
		else if (check_is_double_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\"'))
		{
			start++;
			while (start < end && !check_is_double_quote(cmd_line[start]))
				start++;
			start++;
		}
		else
		{
			while (start < end)
			{
				if (check_is_single_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\''))
					break ;
				if (check_is_double_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\"'))
					break ;
				start++;
			}
		}
		cnt_string++;
	}
	return (cnt_string);
}

s_str_info *make_quote_string(char *cmd_line, int start, int end)
{
	int len_string;
	int i;
	s_str_info *str_info;

	len_string = count_quote_string(cmd_line, start, end);
	i = 0;
	str_info = malloc(sizeof(s_str_info) * (len_string + 1));
	if (str_info == 0)
	{
		printf("malloc error");
		exit(1);
	}
	str_info[len_string].str = 0;
	str_info[len_string].str_len = 0;
	str_info[len_string].str_type = NUL;
	while (start < end)
	{
		if (check_is_single_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\''))
		{
			int j;
			start++;
			j = start;
			while (start < end && !check_is_single_quote(cmd_line[start]))
				start++;
			str_info[i].str = make_str(cmd_line, j, start - 1);
			start++;
			str_info[i].str_len = ft_strlen(str_info[i].str);
			str_info[i].str_type = SINGLE_QUOTE;
		}
		else if (check_is_double_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\"'))
		{
			int j;
			start++;
			j = start;
			while (start < end && !check_is_double_quote(cmd_line[start]))
				start++;
			str_info[i].str = make_str(cmd_line, j, start - 1);
			start++;
			str_info[i].str_len = ft_strlen(str_info[i].str);
			str_info[i].str_type = DOUBLE_QUOTE;
		}
		else
		{
			int j;
			j = start;
			while (start < end)
			{
				if (check_is_single_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\''))
					break ;
				if (check_is_double_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\"'))
					break ;
				start++;
			}
			str_info[i].str = make_str(cmd_line, j, start - 1);
			str_info[i].str_len = ft_strlen(str_info[i].str);
			str_info[i].str_type = STRING;
		}
		i++;
	}
	return (str_info);
}

// word + (redi, pipe, andif, orif, equal, lbra, rbra, whitespace)
t_symbol	parse_word(char *cmd_line, int *end, s_str_info **str_info)
{
	int start;

	start = *end;
	while (cmd_line[*end])
	{
		if (check_is_single_quote(cmd_line[*end]))
			parse_single_quote_string(cmd_line, end);
		else if (check_is_double_quote(cmd_line[*end]))
			parse_double_quote_string(cmd_line, end);
		else if (check_is_seperator(cmd_line[*end]))
			break ;
		else
			(*end)++;
	}
	*str_info = make_quote_string(cmd_line, start, *end);
	return (WORD);
}

t_symbol	parse_branket(char ch, int *end)
{
	(*end)++;
	if (ch == '(')
		return (L_BRA);
	else
		return (R_BRA);
}

void	parse_single_quote_string(char *cmd_line, int *end)
{
	if (check_is_close_quote(cmd_line, *end, '\''))
	{
		(*end)++;
		while (cmd_line[*end] && !check_is_single_quote(cmd_line[*end]))
			(*end)++;
		(*end)++;
	}
	else
	{
		(*end)++;
		while (cmd_line[*end] && !check_is_double_quote(cmd_line[*end]) \
		&& !check_is_seperator(cmd_line[*end]))
			(*end)++;
	}
}

void	parse_double_quote_string(char *cmd_line, int *end)
{
	if (check_is_close_quote(cmd_line, *end, '\"'))
	{
		(*end)++;
		while (cmd_line[*end] && !check_is_double_quote(cmd_line[*end]))
			(*end)++;
		(*end)++;
	}
	else
	{
		(*end)++;
		while (cmd_line[*end] && !check_is_single_quote(cmd_line[*end]) \
		&& !check_is_seperator(cmd_line[*end]))
			(*end)++;
	}
}
