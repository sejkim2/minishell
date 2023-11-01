/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:45:56 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/31 20:13:20 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_file(t_tree_node *child, char ***env)
{
	int		fd_flag;

	fd_flag = 0;
	while (child)
	{
		if (child->symbol == REDIRECTION_LIST)
			fd_flag = run_redirection_list(child, env);
		child = child->next;
		if (fd_flag == -1)
			break;
	}
	return (fd_flag);
}

void	free_cmd(t_cmd *cmd_info)
{
	free_str(cmd_info->cmd);
	free_str(cmd_info->input);
	free_arr(cmd_info->cmd_line);
}

void	run_simple_command(t_tree_node *node, char ***env, t_tree_node *root)
{
	t_tree_node	*child;
	t_cmd		cmd_info;
	int			fd_flag;

	cmd_info.input = ft_strdup(node->token->value);
	parser_env_in_tree(node, *env);
	make_cmd_info(&cmd_info, node->child_list);
	child = node->child_list;
	fd_flag = redirect_file(child, env);
	if (fd_flag)
		g_exit_status = 1;
	else if (cmd_info.cmd)
	{
		if (*cmd_info.input && !*cmd_info.cmd)
			;
		else if (!run_builtin(cmd_info, env, root))
			run_execve(cmd_info, *env);
	}
	free_cmd(&cmd_info);
}
