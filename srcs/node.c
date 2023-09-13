/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:03:01 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/13 18:05:15 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_token(t_token *token, t_symbol symbol, char *value)
{
	token->symbol = symbol;
	token->value = value;
}

t_token	*make_token(t_symbol symbol, char *value)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == 0)
		return (0);
	init_token(new_token, symbol, value);
	return (new_token);
}

t_token_node	*make_node(t_token *token)
{
	int				i;
	t_token_node	*new_node;

	i = 0;
	new_node = (t_token_node *)malloc(sizeof(t_token_node));
	if (new_node == 0)
		return (0);
	new_node->token = token;
	new_node->next = 0;
	return (new_node);
}