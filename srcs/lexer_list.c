/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:13:44 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/20 13:42:19 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_linked_list	*make_list()
{
	t_linked_list	*new_list;

	new_list = (t_linked_list *)malloc(sizeof(t_linked_list));
	new_list->num_of_node = 0;
	new_list->head = 0;
	new_list->tail = 0;
	return (new_list);
}

void	push_back_list(t_linked_list *list, t_token_node *node)
{
	if (list->num_of_node == 0)
		list->head = node;
	else
		list->tail->next = node;
	list->tail = node;
	list->num_of_node++;
}

t_token_node *pop_list(t_linked_list *list)
{
	t_token_node *pop_node;

	pop_node = list->head;
	list->head = list->head->next;
	(list->num_of_node)--;
	return (pop_node);
}
