/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_function_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:31:05 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/28 17:37:12 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*remove : line 30*/
/*| or ls |*/
int	parse_pipeline(t_linked_list *list, t_tree_node *parent, char **env)
{
	t_tree_node	*node;

	node = make_tree_node(list, COMMAND);
	addchild(parent, node);
	if (parse_command(list, node, env) == -1)
		return (-1);
	if (accept(list, PIPE))
	{
		node = make_tree_node(list, list->head->token->symbol);
		next_symbol(list);
		addchild(parent, node);
		if (list->num_of_node == 0)
			return (parse_error(node->token->value));
		node = make_tree_node(list, PIPELINE);
		addchild(parent, node);
		if (parse_pipeline(list, node, env) == -1)
			return (-1);
	}
	return (1);
}

/*remove : line 54*/
/*remove : line 59*/
int	parse_list(t_linked_list *list, t_tree_node *parent, char **env)
{
	t_tree_node	*node;
	t_symbol	symbol;

	node = make_tree_node(list, PIPELINE);
	addchild(parent, node);
	if (parse_pipeline(list, node, env) == -1)
		return (-1);
	if (accept(list, AND_IF) || accept(list, OR_IF))
	{
		node = make_tree_node(list, list->head->token->symbol);
		next_symbol(list);
		addchild(parent, node);
		if (list->num_of_node == 0)
			return (parse_error(node->token->value));
		symbol = list->head->token->symbol;
		if (symbol == PIPE || symbol == AND_IF || \
		symbol == OR_IF || symbol == R_BRA)
			return (parse_error(list->head->token->value));
		node = make_tree_node(list, LIST);
		addchild(parent, node);
		return (parse_list(list, node, env));
	}
	return (1);
}

/*
line 92
ex1) (cmd1) cmd2
ex2) (cmd1) (cmd2)
*/
int	parse_subshell(t_linked_list *list, t_tree_node *parent, char **env)
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
	if (parse_list(list, node, env) == -1)
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
			return (parse_error(list->head->token->value));
	}
	return (1);
}
