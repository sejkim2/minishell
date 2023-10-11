/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:11:28 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/06 14:29:25 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	check_parse_redirection_error(char *cmd_line, int index)
{
	if (!cmd_line[index])
		return (print_unexpected_token_syntax_error(0, '\n'));
	if (cmd_line[index] == '(' || cmd_line[index] == ')' \
	|| cmd_line[index] == '&' || cmd_line[index] == '|')
		return (print_unexpected_token_syntax_error(0, cmd_line[index]));
	if (cmd_line[index] == '<')
	{
		if (cmd_line[index + 1] && cmd_line[index + 1] == '<')
			return (print_unexpected_token_syntax_error("<<", '\0'));
		else
			return (print_unexpected_token_syntax_error(0, cmd_line[index]));
	}
	if (cmd_line[index] == '>')
	{
		if (cmd_line[index + 1] && cmd_line[index + 1] == '>')
			return (print_unexpected_token_syntax_error(">>", '\0'));
		else
			return (print_unexpected_token_syntax_error(0, cmd_line[index]));
	}
	return (1);
}

int	parse_redirection(char *cmd_line, int *end, s_str_info **str_info)
{
	int	start;

	while (cmd_line[*end] && check_is_white_space(cmd_line[*end]))
		(*end)++;
	if (check_parse_redirection_error(cmd_line, *end) == -1)
		return (-1);
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
	return (1);
}
