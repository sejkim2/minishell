/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:55:41 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/31 20:26:43 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_token_node(t_token_node *node, int is_remove_token)
{
	if (is_remove_token == 1)
		free_token(node->token);
	node->next = 0;
	if (node)
	{
		free(node);
		node = 0;
	}
	return (0);
}

char	*free_list(t_linked_list *list, int is_remove_token)
{
	t_token_node	*cur;
	t_token_node	*del_node;

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
		free_token_node(del_node, is_remove_token);
	}
	if (cur)
		free_token_node(cur, is_remove_token);
	if (list)
	{
		free(list);
		list = 0;
	}
	return (0);
}
