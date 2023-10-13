/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:45:56 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/13 19:55:31 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_simple_command_nonpipe(t_tree_node *node, char **env)
{
	t_tree_node	*child;
	int			o_fd[2];
	t_cmd		cmd_info;

	o_fd[0] = dup(0);
	o_fd[1] = dup(1);
	change_env(node, env);
	cmd_info = make_cmd_info(node->child_list, env);
	while (child)
	{
		if (child->symbol == REDIRECTION_LIST)
			run_redirection_list(child);
		child = child->next;
	}
	if (!run_builtin(cmd_info, env))
		run_execve(cmd_info, env);
	recover_std_fd(o_fd);
}

void	run_simple_command(t_tree_node *node, int *iput, int *oput, char **env)
{
	t_tree_node	*child;

	child = node->child_list;
	dup2(iput[0], 0);
	dup2(oput[1], 1);
	while (child)
	{
		if (child->symbol == REDIRECTION_LIST)
			run_redirection_list(child);
		child = child->next;
	}
	run_simple_command_element(node->child_list, env);
}

void	run_simple_command_element(t_tree_node *node, char **env)
{
	run_word(cmd_info, env);
}


void	run_word(t_cmd cmd_info, char **env)
{

	cmd_info.cmd = get_path(cmd_info.cmd); // 경로 찾아서 붙여주는 함수.
	if (access(cmd_info.cmd, X_OK) == -1)
	{
		printf("minishell: %s: %s\n", cmd_info.cmd, strerror(errno));
		exit(1);
	}
	execve(cmd_info.cmd, cmd_info.cmd_line, env);
}
