/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:28:08 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/18 16:47:05 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(char **cmd_argv, char **env)
{
	char	buff[PATH_MAX];
	int		cmd_argc;

	g_exit_status = 0;
	cmd_argc = cnt_line(cmd_argv);
	if (!cmd_argc)
	{
		if (chdir(get_envval("HOME", env)) == -1)
		{
			ft_stderror_print("cd", *cmd_argv, "HOME not set");
			g_exit_status = 1;
		}
	}
	else
	{
		if (chdir(*cmd_argv) == -1)
		{
			ft_stderror_print("cd", *cmd_argv, strerror(errno));
			g_exit_status = 1;
		}
	}
}
