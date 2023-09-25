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

static	void	parse_if_one_token(char *cmd_line, int *end)
{
	(*end)++;
	if (!cmd_line[*end])
		print_unexpected_token_syntax_error('\n');
}

t_symbol	parse_pipe_or_orif_or_andif(char *cmd_line, char ch, int *end)
{
	(*end)++;
	if (!cmd_line[*end])
		print_unexpected_token_syntax_error('|');
	if (ch == '|')
	{
		if (ch == cmd_line[*end])
		{	
			parse_if_one_token(cmd_line, end);
			return (OR_IF);
		}
		else
			return (PIPE);
	}
	else
	{
		if (ch == cmd_line[*end])
		{
			parse_if_one_token(cmd_line, end);
			return (AND_IF);
		}
		else
			print_unexpected_token_syntax_error('&');
	}
	return (WORD);
}
