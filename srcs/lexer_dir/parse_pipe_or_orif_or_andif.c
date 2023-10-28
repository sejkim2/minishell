/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_or_orif_or_andif.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:44:19 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/28 15:05:21 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	parse_if_one_token(char *cmd_line, int *end)
{
	(*end)++;
	while (cmd_line[*end] && check_is_white_space(cmd_line[*end]))
		(*end)++;
	return (1);
}

int	parse_pipe_or_orif_or_andif(char *cmd_line, char ch, \
int *end, t_token *token)
{
	(*end)++;
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
			return (print_unexpected_token_syntax_error(0, '&'));
	}
	return (1);
}
