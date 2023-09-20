/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:40:01 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/20 17:08:03 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_symbol	parse_redirection(char *cmd_line, int *end)
{
	while (cmd_line[*end] && check_is_white_space(cmd_line[*end]))
		(*end)++;
	if (!cmd_line[*end])
		lexer_error();
	if (cmd_line[*end] == '(' || cmd_line[*end] == ')' \
	|| cmd_line[*end] == '<' || cmd_line[*end] == '>')
		lexer_error();
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
	return (REDIRECTION);
}

// word + (redi, pipe, andif, orif, equal, lbra, rbra, whitespace)
t_symbol	parse_word(char *cmd_line, int *end)
{
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
	return (WORD);
}

t_symbol	parse_equal_or_branket(char ch, int *end)
{
	(*end)++;
	if (ch == '=')
		return (EQUAL);
	else if (ch == '(')
		return (L_BRA);
	else
		return (R_BRA);
}
