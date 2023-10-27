/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:54:45 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/27 15:51:04 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_cmd cmd_info, char ***env, t_tree_node *root)
{
	cmd_info.cmd_line++;
	if (!ft_strcmp(cmd_info.cmd, "cd"))
		builtin_cd(cmd_info.cmd_line, *env);
	else if (!ft_strcmp(cmd_info.cmd, "echo"))
		builtin_echo(cmd_info.cmd_line);
	else if (!ft_strcmp(cmd_info.cmd, "env"))
		builtin_env(cmd_info.cmd_line, *env);
	else if (!ft_strcmp(cmd_info.cmd, "exit"))
		builtin_exit(cmd_info.cmd_line, root);
	else if (!ft_strcmp(cmd_info.cmd, "export"))
		builtin_export(cmd_info.cmd_line, env);
	else if (!ft_strcmp(cmd_info.cmd, "pwd"))
		builtin_pwd(*env);
	else if (!ft_strcmp(cmd_info.cmd, "unset"))
		builtin_unset(cmd_info.cmd_line, env);
	else
		return (0);
	return (1);
}

static void	check_file_system(t_cmd cmd_info, char **env)
{
	struct stat	file_info;

	stat(cmd_info.cmd, &file_info);
	if (S_ISDIR(file_info.st_mode))
	{
		if (ft_strchr(cmd_info.cmd, '/'))
		{
			ft_stderror_print(cmd_info.cmd, NULL, "is a direcotry");
			exit(126);
		}
		else
		{
			ft_stderror_print(cmd_info.cmd, NULL, "command not found");
			exit(127);
		}
	}
	if (execve(cmd_info.cmd, cmd_info.cmd_line, env) == -1)
		system_call_error();
}

static void	check_file_exist(t_cmd cmd_info, char **env)
{
	if (!*cmd_info.cmd)
	{
		ft_stderror_print(cmd_info.input, NULL, "command not found");
		exit(127);
	}
	else if (access(cmd_info.cmd, F_OK) == -1)
	{
		if (ft_strchr(cmd_info.cmd, '/'))
			ft_stderror_print(cmd_info.cmd, NULL, "No such file or directory");
		else
			ft_stderror_print(cmd_info.cmd, NULL, "command not found");
		exit(127);
	}
	else if (access(cmd_info.cmd, X_OK) == -1)
	{
		ft_stderror_print(cmd_info.cmd, NULL, "Permission denied");
		exit(126);
	}
	else
		check_file_system(cmd_info, env);
}

void	run_execve(t_cmd cmd_info, char **env)
{
	pid_t	exe_fork;
	char	*tmp;

	tmp = cmd_info.cmd;
	exe_fork = fork();
	if (exe_fork == -1)
		system_call_error();
	if (exe_fork == 0)
	{
		set_default_signal();
		cmd_info.cmd = get_path(tmp, env);
		check_file_exist(cmd_info, env);
	}
	else
	{
		set_blocking_signal();
		wait_record_status();
	}
}
