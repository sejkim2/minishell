/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:44:36 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/31 11:24:21 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_subshell_redir(t_tree_node *node, char ***env)
{
	int		fd_flag;

	if (node == NULL)
		return (0);
	fd_flag = 0;
	if (node->symbol == REDIRECTION_LIST)
		fd_flag = run_redirection_list(node, env);
	return (fd_flag);
}

void	run_command_nonpipe(t_tree_node *node, char ***env, t_tree_node *root)
{
	t_tree_node	*child;
	pid_t		sub_pro;

	child = node->child_list;
	if (child->symbol == SIMPLE_COMMAND)
		run_simple_command(child, env, root);
	else
	{
		sub_pro = fork();
		if (sub_pro == -1)
			system_call_error();
		if (sub_pro == 0)
		{
			root->in_fork = 1;
			if (run_subshell_redir(child->next, env) == 0)
				run_list(child->child_list->next, env, root);
			exit(g_exit_status);
		}
		else
			wait_record_status(sub_pro);
	}
}

void	run_command_pipe(t_tree_node *node, char ***env, t_tree_node *root)
{
	t_tree_node	*child;
	pid_t		sub_pro;

	child = node->child_list;
	if (child->symbol == SIMPLE_COMMAND)
		run_simple_command(child, env, root);
	else
	{
		sub_pro = fork();
		if (sub_pro == -1)
			system_call_error();
		if (sub_pro == 0)
		{
			root->in_fork = 1;
			if (run_subshell_redir(child->next, env) == 0)
				run_list(child->child_list->next, env, root);
			exit(g_exit_status);
		}
		else
			wait_record_status(sub_pro);
	}
}
