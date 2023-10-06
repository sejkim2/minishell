/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:57:18 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/06 13:48:27 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_symbol	next_symbol(t_linked_list *list)
{
	t_token_node	*node;
	t_symbol		symbol;

	node = pop_list(list);
	symbol = node->token->symbol;
	return (symbol);
}

int	accept(t_linked_list *list, t_symbol symbol)
{
	if (list->num_of_node == 0)
		return (0);
	return (list->head->token->symbol == symbol);
}

int	expect(t_linked_list *list, t_symbol symbol)
{
	if (!accept(list, symbol))
	{
		return (parse_error(list->head->token->value));
		// return (0);
	}
	else
		return (1);
}

t_tree_node	*parser(t_linked_list *list)
{
	t_tree_node		*root;
	t_tree_node		*node;
	t_token_node	*head;
    int num_of_node;
    int syntax_error;

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
    /*   pipe, and, or + cmd --> parse error */
	else
		syntax_error = parse_error(list->head->token->value);
    if (syntax_error == -1)
    {
        list->head = head;
        list->num_of_node = num_of_node;
        free_list(list);
        free_tree(root);
        return (0);
    }
	tree_traverse(root, 0);
	list->head = head;
    list->num_of_node = num_of_node;
	return (root);
}
