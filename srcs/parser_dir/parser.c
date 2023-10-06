/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:57:18 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/06 16:38:38 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	reset_list_info(t_linked_list *list, \
t_token_node *head, int num_of_node)
{
	list->head = head;
	list->num_of_node = num_of_node;
}

static	t_tree_node	*free_tree_and_list(t_linked_list *list, t_tree_node *root, \
t_token_node *head, int num_of_node)
{
	reset_list_info(list, head, num_of_node);
	free_list(list);
	free_tree(root);
	return (0);
}

t_tree_node	*parser(t_linked_list *list)
{
	t_tree_node		*root;
	t_tree_node		*node;
	t_token_node	*head;
	int				num_of_node;
	int				syntax_error;

	head = list->head;
	num_of_node = list->num_of_node;
	root = make_tree_node(list, ROOT);
	root->token = 0;
	syntax_error = 1;
	if (accept(list, WORD) || accept(list, REDIRECTION) || accept(list, L_BRA))
	{
		node = make_tree_node(list, LIST);
		addchild(root, node);
		syntax_error = parse_list(list, node);
	}
	else
		syntax_error = parse_error(list->head->token->value);
	if (syntax_error == -1)
		return (free_tree_and_list(list, root, head, num_of_node));
	tree_traverse(root, 0);
	reset_list_info(list, head, num_of_node);
	return (root);
}
