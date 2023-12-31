/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_node_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:03:01 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/31 11:24:36 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	init_new_token(t_token *token)
{
	token->symbol = WORD;
	token->redir_type = NO_REDIR;
	token->value = 0;
	token->hd_name = 0;
	token->str_info = 0;
}

t_token	*make_token(void)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == 0)
		malloc_error();
	init_new_token(new_token);
	return (new_token);
}

t_token_node	*make_node(t_token *token)
{
	t_token_node	*new_node;

	new_node = (t_token_node *)malloc(sizeof(t_token_node));
	if (new_node == 0)
		malloc_error();
	new_node->token = token;
	new_node->next = 0;
	return (new_node);
}
