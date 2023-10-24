/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:00:13 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/24 13:33:34 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_andif_list(t_tree_node *node, char ***env)
{
	t_tree_node	*child;
	int			o_fd[2];

	store_std_fd(o_fd);
	child = node->child_list;
	if (!g_exit_status)
		run_pipeline(child, env, LIST);
	child = child->next;
	if (child)
	{
		recover_std_fd(o_fd);
		if (child->symbol == AND_IF)
			run_andif_list(child->next, env);
		else if (child->symbol == OR_IF)
			run_orif_list(child->next, env);
	}
}

void	run_orif_list(t_tree_node *node, char ***env)
{
	t_tree_node	*child;
	int			o_fd[2];

	store_std_fd(o_fd);
	child = node->child_list;
	if (g_exit_status)
		run_pipeline(child, env, LIST);
	child = child->next;
	if (child)
	{
		recover_std_fd(o_fd);
		if (child->symbol == AND_IF)
			run_andif_list(child->next, env);
		else if (child->symbol == OR_IF)
			run_orif_list(child->next, env);
	}
}

void	run_list(t_tree_node *node, char ***env)
{
	t_tree_node	*child;
	int			o_fd[2];

	store_std_fd(o_fd);
	child = node->child_list;
	run_pipeline(child, env, LIST);
	child = child->next;
	if (child)
	{
		recover_std_fd(o_fd);
		if (child->symbol == AND_IF)
			run_andif_list(child->next, env);
		else if (child->symbol == OR_IF)
			run_orif_list(child->next, env);
	}
}
