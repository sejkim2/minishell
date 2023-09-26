/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_function_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:31:05 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/25 20:38:06 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipeline(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;

	node = make_tree_node(list, COMMAND);
	addchild(parent, node);
	if (parse_command(list, node) == -1)
		return (-1);
	if (accept(list, PIPE))
	{
		node = make_tree_node(list, list->head->token->symbol);
		next_symbol(list);
		if (list->num_of_node == 0)
			return (parse_error());
		addchild(parent, node);
		node = make_tree_node(list, PIPELINE);
		addchild(parent, node);
		if (parse_pipeline(list, node) == -1)
			return (-1);
	}
	return (1);
}

int	parse_list(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;
	t_symbol	symbol;


	node = make_tree_node(list, PIPELINE);
	addchild(parent, node);
	if (parse_pipeline(list, node) == -1)
		return (-1);
	if (accept(list, AND_IF) || accept(list, OR_IF))
	{
		node = make_tree_node(list, list->head->token->symbol);
		next_symbol(list);
		if (list->num_of_node == 0)
			return (parse_error());
		addchild(parent, node);
		symbol = list->head->token->symbol;
		if (symbol == PIPE || symbol == AND_IF || \
		symbol == OR_IF || symbol == R_BRA)
			return (parse_error());
		node = make_tree_node(list, LIST);
		addchild(parent, node);
		return (parse_list(list, node));
	}
	return (1);
}

int	parse_subshell(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;
	t_symbol	symbol;

	if (expect(list, L_BRA) == -1)
		return (-1);
	node = make_tree_node(list, list->head->token->symbol);
	next_symbol(list);
	addchild(parent, node);
	node = make_tree_node(list, LIST);
	addchild(parent, node);
	if (parse_list(list, node) == -1)
		return (-1);
	if (expect(list, R_BRA) == -1)
		return (-1);
	node = make_tree_node(list, list->head->token->symbol);
	next_symbol(list);
	addchild(parent, node);
	if (list->num_of_node > 0)
	{
		symbol = list->head->token->symbol;
		if (symbol == L_BRA || symbol == WORD)
			return (parse_error());
	}
	return (1);
}
