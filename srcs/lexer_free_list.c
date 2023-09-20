/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:55:41 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/20 13:42:16 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*free_token(t_token *token)
{
	free(token->token_value);
	free(token);
	return (0);
}

char	*free_node(t_token_node *node)
{
	free_token(node->token);
	free(node);
	return (0);
}

char	*free_list(t_linked_list *list)
{
	t_token_node	*cur;
	t_token_node	*del_node;

	free(list->cmd_line);
	cur = list->head;
	list->head = 0;
	list->tail = 0;
	if (list->num_of_node == 0)
	{
		free(list);
		return (0);
	}
	while (cur->next)
	{
		del_node = cur;
		cur = cur->next;
		free_node(del_node);
	}
	free_node(cur);
	free(list);
	return (0);
}
