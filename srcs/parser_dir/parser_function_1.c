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

void	parse_pipeline(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;

	node = make_tree_node(list, COMMAND);
	addchild(parent, node);
	parse_command(list, node);
	if (accept(list, PIPE))
	{
		node = make_tree_node(list, list->head->token->symbol);
		next_symbol(list);
		if (list->num_of_node == 0)
			parse_error();
		addchild(parent, node);
		node = make_tree_node(list, PIPELINE);
		addchild(parent, node);
		parse_pipeline(list, node);
	}
}

void	parse_list(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;
	t_symbol	symbol;

	node = make_tree_node(list, PIPELINE);
	addchild(parent, node);
	parse_pipeline(list, node);
	if (accept(list, AND_IF) || accept(list, OR_IF))
	{
		node = make_tree_node(list, list->head->token->symbol);
		next_symbol(list);
		if (list->num_of_node == 0)
			parse_error();
		addchild(parent, node);
		symbol = list->head->token->symbol;
		if (symbol == PIPE || symbol == AND_IF || \
		symbol == OR_IF || symbol == R_BRA)
			parse_error();
		node = make_tree_node(list, LIST);
		addchild(parent, node);
		parse_list(list, node);
	}
}

void	parse_subshell(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;
	t_symbol	symbol;

	expect(list, L_BRA);
	node = make_tree_node(list, list->head->token->symbol);
	next_symbol(list);
	addchild(parent, node);
	node = make_tree_node(list, LIST);
	addchild(parent, node);
	parse_list(list, node);
	expect(list, R_BRA);
	node = make_tree_node(list, list->head->token->symbol);
	next_symbol(list);
	addchild(parent, node);
	if (list->num_of_node > 0)
	{
		symbol = list->head->token->symbol;
		if (symbol == L_BRA || symbol == WORD)
			parse_error();
	}
}
