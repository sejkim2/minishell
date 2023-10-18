/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:45:56 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/18 16:44:55 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_simple_command_nonpipe(t_tree_node *node, char ***env)
{
	t_tree_node	*child;
	int			o_fd[2];
	t_cmd		cmd_info;
	int			fd_flag;

	fd_flag = 0;
	store_std_fd(o_fd);
	expand_env(node, *env);
	cmd_info = make_cmd_info(node->child_list, *env);
	child = node->child_list;
	while (child)
	{
		if (child->symbol == REDIRECTION_LIST)
			fd_flag = run_redirection_list(child);
		child = child->next;
	}
	if (cmd_info.cmd && fd_flag == 0)
	{
		if (!run_builtin(cmd_info, env))
			run_execve(cmd_info, *env);
	}
	else
		g_exit_status = 1;
	recover_std_fd(o_fd);
}

// void	run_simple_command_firstpipe(t_tree_node *node, int *oput, char ***env)
// {
// 	t_tree_node	*child;
// 	t_cmd		cmd_info;

// 	expand_env(node, *env);
// 	cmd_info = make_cmd_info(node->child_list, *env);
// 	child = node->child_list;
// 	dup2(oput[0], 1);
// 	while (child)
// 	{
// 		if (child->symbol == REDIRECTION_LIST)
// 			run_redirection_list(child);
// 		child = child->next;
// 	}
// 	if (cmd_info.cmd)
// 	{
// 		if (!run_builtin(cmd_info, env))
// 			run_execve(cmd_info, *env);
// 	}
// }

// void	run_simple_command_middlepipe(t_tree_node *node, int *iput, int *oput, char ***env)
// {
// 	t_tree_node	*child;
// 	t_cmd		cmd_info;

// 	expand_env(node, *env);
// 	cmd_info = make_cmd_info(node->child_list, *env);
// 	child = node->child_list;
// 	dup2(iput[0], 0);
// 	dup2(oput[1], 1);
// 	while (child)
// 	{
// 		if (child->symbol == REDIRECTION_LIST)
// 			run_redirection_list(child);
// 		child = child->next;
// 	}
// 	if (cmd_info.cmd)
// 	{
// 		if (!run_builtin(cmd_info, env))
// 			run_execve(cmd_info, *env);
// 	}
// }

// void	run_simple_command_lastpipe(t_tree_node *node, int *iput, char ***env)
// {
// 	t_tree_node	*child;
// 	t_cmd		cmd_info;

// 	expand_env(node, *env);
// 	cmd_info = make_cmd_info(node->child_list, *env);
// 	child = node->child_list;
// 	dup2(iput[0], 0);
// 	while (child)
// 	{
// 		if (child->symbol == REDIRECTION_LIST)
// 			run_redirection_list(child);
// 		child = child->next;
// 	}
// 	if (cmd_info.cmd)
// 	{
// 		if (!run_builtin(cmd_info, env))
// 			run_execve(cmd_info, *env);
// 	}
// }
