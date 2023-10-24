/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:45:56 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/24 13:45:58 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_simple_command(t_tree_node *node, char ***env)
{
	t_tree_node	*child;
	t_cmd		cmd_info;
	int			fd_flag;

	expand_env(node, *env);
	cmd_info = make_cmd_info(node->child_list, *env);
	child = node->child_list;
	fd_flag = 0;
	while (child)
	{
		if (child->symbol == REDIRECTION_LIST)
			fd_flag = run_redirection_list(child, env);
		child = child->next;
		if (fd_flag == -1)
			break ;
	}
	if (cmd_info.cmd && fd_flag == 0)
	{	
		if (!run_builtin(cmd_info, env))
			run_execve(cmd_info, *env);
	}
	else
		g_exit_status = 1;
}
