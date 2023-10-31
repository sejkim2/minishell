/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:22:41 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/31 20:25:19 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*free_str_info(t_str_info *str_info)
{
	int	i;

	i = 0;
	while (str_info[i].str_type != NUL)
	{
		if (str_info[i].str)
		{
			free(str_info[i].str);
			str_info[i].str = 0;
		}
		i++;
	}
	if (str_info)
	{
		free(str_info);
		str_info = 0;
	}
	return (0);
}

char	*free_token(t_token *token)
{
	if (token->value)
	{
		free(token->value);
		token->value = 0;
	}
	if (token->str_info)
	{
		free_str_info(token->str_info);
		token->str_info = 0;
	}
	if (token->hd_name)
	{
		unlink(token->hd_name);
		free(token->hd_name);
		token->hd_name = 0;
	}
	if (token)
	{
		free(token);
		token = 0;
	}
	return (0);
}

char	*free_tree_node(t_tree_node *node, int is_remove_token)
{
	node->next = 0;
	node->child_list = 0;
	if (is_remove_token == 1)
		free_token(node->token);
	if (node)
	{
		free(node);
		node = 0;
	}
	return (0);
}

char	*free_tree(t_tree_node *parent, int is_remove_token)
{
	t_tree_node	*child;
	t_tree_node	*remove_node;

	child = parent->child_list;
	if (child)
	{
		while (child)
		{
			remove_node = child;
			child = child->next;
			if (remove_node->child_list == 0)
				free_tree_node(remove_node, is_remove_token);
			else
				free_tree(remove_node, is_remove_token);
		}
	}
	if (parent)
	{	
		free(parent);
		parent = 0;
	}
	return (0);
}
