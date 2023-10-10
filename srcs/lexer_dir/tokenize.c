/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:09:15 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/06 13:34:52 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	parse_redirection__(char *cmd_line, int cur_index, \
int *end, t_token *token)
{
	(*end)++;
	token->redir_type = SINGLE_REDIR;
	if (!cmd_line[*end])
		return (print_unexpected_token_syntax_error(0, '\n'));
	if (cmd_line[cur_index] == '<' && cmd_line[*end] == '>')
	{
		if (cmd_line[*end + 1] && cmd_line[*end + 1] == '>')
			return (print_unexpected_token_syntax_error(">>", 0));
		else
			return (print_unexpected_token_syntax_error(">", '\0'));
	}
	if (cmd_line[cur_index] == '>' && cmd_line[*end] == '<')
	{
		if (cmd_line[*end + 1] && cmd_line[*end + 1] == '<')
			return (print_unexpected_token_syntax_error("<<", 0));
		else
			return (print_unexpected_token_syntax_error("<", '\0'));
	}
	if (cmd_line[cur_index] == cmd_line[cur_index + 1])
	{
		(*end)++;
		token->redir_type = DOUBLE_REDIR;
	}
	token->symbol = REDIRECTION;
	return (parse_redirection(cmd_line, end, &(token->str_info)));
}

t_token_node	*tokenize(char *cmd_line, int *index)
{
	t_token		*token;
	int			end;
	int			syntax_error;

	token = make_token();
	end = *index;
	if (cmd_line[*index] == '<' || cmd_line[*index] == '>')
		syntax_error = parse_redirection__(cmd_line, *index, &end, token);
	else if (cmd_line[*index] == '|' || cmd_line[*index] == '&')
		syntax_error = parse_pipe_or_orif_or_andif(cmd_line, \
	cmd_line[*index], &end, token);
	else if (cmd_line[*index] == '(' || cmd_line[*index] == ')')
		syntax_error = parse_branket(cmd_line[*index], &end, token);
	else
		syntax_error = parse_word(cmd_line, &end, token);
	if (syntax_error == -1)
	{
		free_token(token);
		return (0);
	}
	token->value = make_value(cmd_line, *index, end);
	*index = end;
	return (make_node(token));
}
