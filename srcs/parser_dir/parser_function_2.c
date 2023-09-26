/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_function_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:29:54 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/25 20:38:10 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_simple_command_element(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;
	t_symbol	symbol;

	if (accept(list, WORD) || accept(list, ASSIGNMENT_WORD) \
	|| accept(list, REDIRECTION))
	{
		node = make_tree_node(list, list->head->token->symbol);
		next_symbol(list);
		if (list->num_of_node > 0)
		{
			symbol = list->head->token->symbol;
			if (symbol == L_BRA)
				return (parse_error());
		}
		addchild(parent, node);
		return (1);
	}
	else
		return (parse_error());
}

int	parse_redirection_list(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;
	t_symbol	symbol;

	while (1)
	{
		if (accept(list, REDIRECTION))
		{
			node = make_tree_node(list, list->head->token->symbol);
			next_symbol(list);
			addchild(parent, node);
			if (list->num_of_node > 0)
			{
				symbol = list->head->token->symbol;
				if (symbol == L_BRA)
					return (parse_error());
			}
		}
		else
			break ;
	}
	return (1);
}

int	parse_simple_command(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;

	while (1)
	{
		if (accept(list, WORD) || accept(list, ASSIGNMENT_WORD) \
		|| accept(list, REDIRECTION))
		{
			if (accept(list, REDIRECTION))
			{
				node = make_tree_node(list, REDIRECTION_LIST);
				addchild(parent, node);
				if (parse_redirection_list(list, node) == -1)
					return (-1);
			}
			else
			{
				node = make_tree_node(list, SIMPLE_COMMAND_ELEMENT);
				addchild(parent, node);
				if (parse_simple_command_element(list, node) == -1)
					return (-1);
			}
		}
		else
			break ;
	}
	return (1);
}

int	parse_command(t_linked_list *list, t_tree_node *parent)
{
	t_tree_node	*node;
	int syntax_error;

	if (accept(list, WORD) || accept(list, ASSIGNMENT_WORD) \
	|| accept(list, REDIRECTION))
	{
		node = make_tree_node(list, SIMPLE_COMMAND);
		addchild(parent, node);
		return (parse_simple_command(list, node));
	}
	else if (accept(list, L_BRA))
	{
		node = make_tree_node(list, SUBSHELL);
		addchild(parent, node);
		if (parse_subshell(list, node) == -1)
			return (-1);
		if (accept(list, REDIRECTION))
		{
			node = make_tree_node(list, REDIRECTION_LIST);
			addchild(parent, node);
			return (parse_redirection_list(list, node));
		}
		return (1);
	}
	else
		return (parse_error());
}
