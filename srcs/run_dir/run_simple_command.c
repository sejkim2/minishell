/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:45:56 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/28 15:21:37 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd_info)
{
	if (cmd_info->cmd)
		free(cmd_info->cmd);
	if (cmd_info->input)
		free(cmd_info->input);
	free_arr(cmd_info->cmd_line);
}

void	run_simple_command(t_tree_node *node, char ***env, t_tree_node *root)
{
	t_tree_node	*child;
	t_cmd		cmd_info;
	int			fd_flag;

	cmd_info.input = ft_strdup(node->token->value);
	expand_env(node, *env);
	make_cmd_info(&cmd_info, node->child_list);
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
		if (!run_builtin(cmd_info, env, root))
			run_execve(cmd_info, *env);
	}
	else if (fd_flag)
		g_exit_status = 1;
	free_cmd(&cmd_info);
}
