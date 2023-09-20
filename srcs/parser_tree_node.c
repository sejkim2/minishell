/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:27:52 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/20 20:07:19 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_tree_node(t_linked_list *list, t_tree_node *node, t_symbol symbol)
{
	node->token = list->head->token;
	node->symbol = symbol;
}

t_tree_node	*make_tree_node(t_linked_list *list, t_symbol symbol)
{
	t_tree_node	*node;

	node = (t_tree_node *)malloc(sizeof(t_tree_node));
	node->num_of_child = 0;
	node->next = 0;
	node->child_list = 0;
	init_tree_node(list, node, symbol);
	return (node);
}

void	addchild(t_tree_node *parent, t_tree_node *child)
{
	t_tree_node	*cur;

	cur = parent->child_list;
	if (parent->num_of_child == 0)
		parent->child_list = child;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = child;
	}
	(parent->num_of_child)++;
}
