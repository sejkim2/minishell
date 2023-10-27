/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_function_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:31:05 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/27 15:12:58 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*remove : line 30*/
/*| or ls |*/
int	parse_pipeline(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;
	int			error_flag;

	node = make_tree_node(list, COMMAND);
	addchild(parent, node);
	error_flag = parse_command(list, node);
	if (error_flag < 0)
		return (error_flag);
	if (accept(list, PIPE))
	{
		node = make_tree_node(list, list->head->token->symbol);
		next_symbol(list);
		addchild(parent, node);
		if (list->num_of_node == 0)
			return (parse_error(node->token->value));
		node = make_tree_node(list, PIPELINE);
		addchild(parent, node);
		error_flag = parse_pipeline(list, node);
		if (error_flag < 0)
			return (error_flag);
	}
	return (1);
}

/*remove : line 54*/
/*remove : line 59*/
int	parse_list(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;
	t_symbol	symbol;
	int			error_flag;

	node = make_tree_node(list, PIPELINE);
	addchild(parent, node);
	error_flag = parse_pipeline(list, node);
	if (error_flag < 0)
		return (error_flag);
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
		return (parse_list(list, node));
	}
	return (1);
}

/*
line 92
ex1) (cmd1) cmd2
ex2) (cmd1) (cmd2)
*/
int	parse_subshell(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;
	t_symbol	symbol;
	int			error_flag;

	if (expect(list, L_BRA) == -1)
		return (-1);
	node = make_tree_node(list, list->head->token->symbol);
	next_symbol(list);
	addchild(parent, node);
	node = make_tree_node(list, LIST);
	addchild(parent, node);
	error_flag = parse_list(list, node);
	if (error_flag < 0)
		return (error_flag);
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
