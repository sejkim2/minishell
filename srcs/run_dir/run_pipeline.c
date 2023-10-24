/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipeline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:00:41 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/24 12:11:22 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipe_fd_dup(int *pipe_fd, int flag)
{
	if (flag == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
	}
	else if (flag == 1)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
	}
}

void	run_pipe(t_tree_node *child, char ***env, int *o_fd)
{
	pid_t		c_pro;

	child = child->next;
	if (child->num_of_child == 1)
	{
		c_pro = fork();
		if (c_pro == 0)
		{
			run_command_nonpipe(child->child_list, env, o_fd);
			exit(g_exit_status);
		}
		else
			wait_last_command(c_pro);
	}
	else
		run_pipeline(child, env, o_fd, PIPE);
}

void	run_pipeline(t_tree_node *node, char ***env, int *o_fd, t_symbol before)
{
	int			pipe_fd[2];
	t_tree_node	*child;
	pid_t		c_pro;

	child = node->child_list;
	if (node->num_of_child == 1 && before == LIST)
		return (run_command_nonpipe(child, env, o_fd));
	while (child)
	{
		if (child->symbol == PIPE)
			return (run_pipe(child, env, o_fd));
		pipe(pipe_fd);
		c_pro = fork();
		if (c_pro == 0)
		{
			pipe_fd_dup(pipe_fd, 1);
			run_command_pipe(child, env, o_fd);
			exit(g_exit_status);
		}
		else
		{
			pipe_fd_dup(pipe_fd, 0);
			child = child->next;
		}
	}
}
