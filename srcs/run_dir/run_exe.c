/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:54:45 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/16 14:13:31 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_cmd cmd_info, char **env)
{
	cmd_info.cmd_line++;
	if (!strcmp(cmd_info.cmd, "cd"))
		builtin_cd(cmd_info.cmd_line, env);
	else if (!strcmp(cmd_info.cmd, "echo"))
		builtin_echo(cmd_info.cmd_line, env);
	else if (!strcmp(cmd_info.cmd, "env"))
		builtin_env(cmd_info.cmd_line, env);
	else if (!strcmp(cmd_info.cmd, "exit"))
		builtin_exit(cmd_info.cmd_line, env);
	else if (!strcmp(cmd_info.cmd, "export"))
		builtin_export(cmd_info.cmd_line, env);
	else if (!strcmp(cmd_info.cmd, "pwd"))
		builtin_pwd(env);
	else if (!strcmp(cmd_info.cmd, "unset"))
		builtin_unset(cmd_info.cmd_line, env);
	else
		return (0);
	return (1);
}

void	run_execve(t_cmd cmd_info, char **env)
{
	pid_t	exe_fork;

	exe_fork = fork();
	if (!exe_fork)
		//error
	if (exe_fork == 0)
	{
		cmd_info.cmd = get_path(cmd_info.cmd); // 경로 찾아서 붙여주는 함수.
		if (access(cmd_info.cmd, X_OK) == -1)
		{
			printf("minishell: %s: %s\n", cmd_info.cmd, strerror(errno));
			exit(1);
		}
		if (execve(cmd_info.cmd, cmd_info.cmd_line, env) == -1)
		{
			printf("minishell: %s: %s\n", cmd_info.cmd, strerror(errno));
			exit(1);
		}
	}
}