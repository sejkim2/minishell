/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:22:41 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/26 20:19:33 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*free_str_info(t_str_info *str_info)
{
	int	i;

	i = 0;
	while (str_info[i].str_type != NUL)
	{
		free(str_info[i].str);
		i++;
	}
	free(str_info);
	return (0);
}

char	*free_token(t_token *token)
{
	if (token->value)
		free(token->value);
	if (token->str_info)
		free_str_info(token->str_info);
	if (token->hd_name)
	{
		unlink(token->hd_name);
		free(token->hd_name);
	}
	free(token);
	return (0);
}

char	*free_tree_node(t_tree_node *node)
{
	node->next = 0;
	node->child_list = 0;
	free_token(node->token);
	free(node);
	return (0);
}

char	*free_tree(t_tree_node *parent)
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
				free_tree_node(remove_node);
			else
				free_tree(remove_node);
		}
	}
	free(parent);
	return (0);
}
