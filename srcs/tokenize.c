/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:19:56 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/06 18:17:46 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	set_double_meta_character(char ch, t_type *token_type)
{
	if (ch == '&')
		*token_type = AND_IF;
	else if (ch == '|')
		*token_type = OR_IF;
	else if (ch == '<')
		*token_type = HEREDOC;
	else
		*token_type = APPEND;
}

static	void	set_single_meta_character(char ch, t_type *token_type)
{
	if (ch == '&')
		*token_type = WORD;
	else if (ch == '|')
		*token_type = PIPE;
	else if (ch == '<')
		*token_type = IN_REDIRECTION;
	else if (ch == '>')
		*token_type = OUT_REDIRECTION;
	else if (ch == '(')
		*token_type = LEFT_BLANKET;
	else if (ch == ')')
		*token_type = RIGHT_BLANKET;
	else
		*token_type = DOLLOR_SIGN;
}

static	void	set_other_character(char ch, t_type *token_type)
{
	if (ch == '\'')
		*token_type = SINGLE_QUOTE;
	else if (ch == '\"')
		*token_type = DOUBLE_QUOTE;
	else
		*token_type = DOLLOR_SIGN;
}

static	void	set_token_type(char *cmd_line, int index, t_type *token_type)
{
	char	ch;

	ch = cmd_line[index];
	if (check_is_meta_character(cmd_line, index))
	{
		if ((cmd_line[index] == cmd_line[index + 1]) && \
		(cmd_line[index] != '(' && cmd_line[index] != ')'\
		&& cmd_line[index] != '$'))
			set_double_meta_character(ch, token_type);
		else
			set_single_meta_character(ch, token_type);
	}
	else
		set_other_character(ch, token_type);
}

void	tokenize(t_linked_list *list, char *cmd_line, int *i, \
t_type *token_type)
{
	int		s;

	s = *i;
	if (check_is_meta_character(cmd_line, *i) || check_is_quote(cmd_line, *i))
	{
		set_token_type(cmd_line, *i, token_type);
		if (*token_type == AND_IF || *token_type == OR_IF \
		|| *token_type == HEREDOC || *token_type == APPEND)
		{
			push_back_list(list, make_node(cmd_line, s, s + 1, *token_type));
			*i = *i + 2;
		}
		else
		{
			push_back_list(list, make_node(cmd_line, s, s, *token_type));
			*i = *i + 1;
		}
	}
	else
	{
		while (cmd_line[*i] && !check_is_seperator(cmd_line, *i))
			(*i)++;
		push_back_list(list, make_node(cmd_line, s, *i - 1, *token_type));
	}
}
