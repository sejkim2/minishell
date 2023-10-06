/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_pipe_or_orif_or_andif.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:44:19 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/04 16:55:54 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	parse_if_one_token(char *cmd_line, int *end, t_symbol symbol)
{
	(*end)++;
	while (cmd_line[*end] && check_is_white_space(cmd_line[*end]))
		(*end)++;
	if (!cmd_line[*end])
	{
		if (symbol == OR_IF)
			return (print_unexpected_token_syntax_error("||", '\0'));
		else
			return (print_unexpected_token_syntax_error("&&", '\0'));
	}
	else
		return (1);
}

int	parse_pipe_or_orif_or_andif(char *cmd_line, char ch, int *end, t_token *token)
{
	(*end)++;
	if (!cmd_line[*end])
		return (print_unexpected_token_syntax_error(0, cmd_line[*end - 1]));
	if (ch == '|')
	{
		if (ch == cmd_line[*end])
		{	
			token->symbol = OR_IF;
			return (parse_if_one_token(cmd_line, end, OR_IF));
		}
		else
			token->symbol = PIPE;
	}
	else
	{
		if (ch == cmd_line[*end])
		{
			token->symbol = AND_IF;
			return (parse_if_one_token(cmd_line, end, AND_IF));
		}
		else
			return (print_unexpected_token_syntax_error(0, '&'));
	}
	return (1);
}
