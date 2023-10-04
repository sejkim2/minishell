/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:40:01 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/04 17:14:09 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_redirection(char *cmd_line, int *end, s_str_info **str_info)
{
	int start;

	while (cmd_line[*end] && check_is_white_space(cmd_line[*end]))
		(*end)++;
	if (!cmd_line[*end])
		return (print_unexpected_token_syntax_error(0, '\n'));
	if (cmd_line[*end] == '(' || cmd_line[*end] == ')' \
	|| cmd_line[*end] == '&' || cmd_line[*end] == '|')
		return (print_unexpected_token_syntax_error(0, cmd_line[*end]));
	if (cmd_line[*end] == '<')
	{
		if (cmd_line[*end + 1] && cmd_line[*end + 1] == '<')
			return (print_unexpected_token_syntax_error("<<", '\0'));
		else
			return (print_unexpected_token_syntax_error(0, cmd_line[*end]));
	}
	if (cmd_line[*end] == '>')
	{
		if (cmd_line[*end + 1] && cmd_line[*end + 1] == '>')
			return (print_unexpected_token_syntax_error(">>", '\0'));
		else
			return (print_unexpected_token_syntax_error(0, cmd_line[*end]));
	}
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

// word + (redi, pipe, andif, orif, equal, lbra, rbra, whitespace)
int	parse_word(char *cmd_line, int *end, t_token *token)
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
	token->str_info = make_quote_string(cmd_line, start, *end);
	token->symbol = WORD;
	return (1);
}

int	parse_branket(char ch, int *end, t_token *token)
{
	(*end)++;
	if (ch == '(')
		token->symbol = L_BRA;
	else
		token->symbol = R_BRA;
	return (1);
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
