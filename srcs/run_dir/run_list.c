/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:00:13 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/23 17:34:41 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_list(t_tree_node *node, char ***env, int *o_fd)
{
	t_tree_node	*child;

	child = node->child_list;
	run_pipeline(child, env, o_fd, LIST);
	child = child->next;
	while (child && ((child->symbol == AND_IF && g_exit_status == 0) || (child ->symbol == OR_IF && g_exit_status)))
	{
		recover_std_fd(o_fd);
		child = child->next;
		run_list(child, env, o_fd);
		child = child->next;
	}
}
