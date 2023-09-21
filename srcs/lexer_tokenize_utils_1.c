/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:40:01 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/21 17:37:46 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_symbol	parse_redirection(char *cmd_line, int *end)
{
	while (cmd_line[*end] && check_is_white_space(cmd_line[*end]))
		(*end)++;
	if (!cmd_line[*end])
		print_unexpected_token_syntax_error('\n');
	if (cmd_line[*end] == '(' || cmd_line[*end] == ')' \
	|| cmd_line[*end] == '<' || cmd_line[*end] == '>')
		print_unexpected_token_syntax_error(cmd_line[*end]);
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
	(*end)++;
	while (cmd_line[*end] && !check_is_single_quote(cmd_line[*end]))
		(*end)++;
	if (!check_is_single_quote(cmd_line[*end]))
		lexer_error();
	(*end)++;
}

void	parse_double_quote_string(char *cmd_line, int *end)
{
	(*end)++;
	while (cmd_line[*end] && !check_is_double_quote(cmd_line[*end]))
		(*end)++;
	if (!check_is_double_quote(cmd_line[*end]))
		lexer_error();
	(*end)++;
}
