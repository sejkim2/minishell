/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:55:17 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/31 20:13:29 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_std_fd(int *o_fd)
{
	o_fd[0] = dup(0);
	o_fd[1] = dup(1);
}

void	recover_std_fd(int *o_fd)
{
	close(0);
	close(1);
	dup2(o_fd[0], 0);
	dup2(o_fd[1], 1);
}

void	unlink_tmpfile(t_tree_node *parent, int depth)
{
	t_tree_node	*child;
	t_tree_node	*node;

	node = parent;
	while (node)
	{
		if (node->symbol == REDIRECTION)
		{
			unlink(node->token->hd_name);
			free_str(node->token->hd_name);
			node->token->hd_name = 0;
		}
		node = node->next;
	}
	child = parent->child_list;
	if (child)
	{
		while (child)
		{
			unlink_tmpfile(child, depth + 1);
			child = child->next;
		}
	}
}
