/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:06:44 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/28 17:58:24 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	list_env(char **env, char **cmd_argv)
{
	int		i;

	i = 0;
	if (!cmd_argv)
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
	else
	{
		check_env_dup(env, cmd_argv);
		list_env(cmd_argv, NULL);
	}
}

void	set_env(char **cmd_argv, char **env)
{
	int		i;
	int		j;

	i = 0;
	while (cmd_argv[i])
	{
		j = 0;
		if (cmd_argv[i][j] == '=')
		{
			env_argv_error(cmd_argv[i], 1);
			g_exit_status = 1;
			return ;
		}
		while (cmd_argv[i][j] && cmd_argv[i][j] != '=')
			j++;
		if (cmd_argv[i][j] == '\0')
		{
			env_argv_error(cmd_argv[i], 127);
			g_exit_status = 127;
			return ;
		}
		i++;
	}
	cmd_argv = check_argv_dup(cmd_argv);
	list_env(env, cmd_argv);
}

void	builtin_env(char **cmd_argv, char **env)
{
	int		cmd_argc;

	g_exit_status = 0;
	cmd_argc = cnt_line(cmd_argv);
	if (!cmd_argc)
		list_env(env, NULL);
	else
		set_env(cmd_argv, env);
}
