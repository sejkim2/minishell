/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_pipe_or_orif_or_andif.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:44:19 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/25 20:36:27 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	parse_if_one_token(char *cmd_line, int *end)
{
	(*end)++;
	if (!cmd_line[*end])
		return (print_unexpected_token_syntax_error('\n'));
	else
		return (1);
}

int	parse_pipe_or_orif_or_andif(char *cmd_line, char ch, int *end, t_token *token)
{
	(*end)++;
	if (!cmd_line[*end])
		return (print_unexpected_token_syntax_error('|'));
	if (ch == '|')
	{
		if (ch == cmd_line[*end])
		{	
			token->symbol = OR_IF;
			return (parse_if_one_token(cmd_line, end));
		}
		else
			token->symbol = PIPE;
	}
	else
	{
		if (ch == cmd_line[*end])
		{
			token->symbol = AND_IF;
			return (parse_if_one_token(cmd_line, end));
		}
		else
			return (print_unexpected_token_syntax_error('&'));
	}
	return (1);
}
