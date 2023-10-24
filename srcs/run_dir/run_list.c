/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:00:13 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/24 12:37:00 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_andif_list(t_tree_node *node, char ***env, int *o_fd)
{
	t_tree_node	*child;

	child = node->child_list;
	if (!g_exit_status)
		run_pipeline(child, env, o_fd, LIST);
	child = child->next;
	if (child)
	{
		if (child->symbol == AND_IF)
			run_andif_list(child->next, env, o_fd);
		else if (child->symbol == OR_IF)
			run_orif_list(child->next, env, o_fd);
	}
}

void	run_orif_list(t_tree_node *node, char ***env, int *o_fd)
{
	t_tree_node	*child;

	child = node->child_list;
	if (g_exit_status)
		run_pipeline(child, env, o_fd, LIST);
	child = child->next;
	if (child)
	{
		if (child->symbol == AND_IF)
			run_andif_list(child->next, env, o_fd);
		else if (child->symbol == OR_IF)
			run_orif_list(child->next, env, o_fd);
	}
}

void	run_list(t_tree_node *node, char ***env, int *o_fd)
{
	t_tree_node	*child;

	child = node->child_list;
	run_pipeline(child, env, o_fd, LIST);
	child = child->next;
	if (child)
	{
		if (child->symbol == AND_IF)
			run_andif_list(child->next, env, o_fd);
		else if (child->symbol == OR_IF)
			run_orif_list(child->next, env, o_fd);
	}
}
