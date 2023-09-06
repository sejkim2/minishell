/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:15:29 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/06 18:08:07 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	init_token(t_token *token, t_type check_type, char *value)
{
	token->token_type = check_type;
	token->token_value = value;
}

static	t_token	*make_token(t_type check_type, char *value)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == 0)
		return (0);
	init_token(new_token, check_type, value);
	return (new_token);
}

t_token_node	*make_node(char *cmd_line, int start, \
int end, t_type check_type)
{
	char			*value;
	int				i;
	t_token_node	*new_node;

	value = (char *)malloc(sizeof(char) * (end - start + 2));
	if (value == 0)
		return (0);
	i = 0;
	new_node = (t_token_node *)malloc(sizeof(t_token_node));
	if (new_node == 0)
	{
		free(value);
		return (0);
	}
	while (start <= end)
		value[i++] = cmd_line[start++];
	value[i] = '\0';
	new_node->token = make_token(check_type, value);
	if (new_node->token == 0)
	{
		free(value);
		free(new_node);
		return (0);
	}
	new_node->next = 0;
	return (new_node);
}
