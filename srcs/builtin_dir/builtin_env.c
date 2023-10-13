/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:06:44 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/13 17:36:14 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_env(char **env)
{
	int		idx;

	idx = 0;
	while (env[idx])
	{
		printf("%s\n", env[idx]);
		idx++;
	}
}

static void	list_shv(char **cmd_argv)
{
	int		idx;

	idx = 0;
	while (cmd_argv[idx])
	{
		if (ft_strchr(cmd_argv[idx], '='))
			printf("%s\n", cmd_argv[idx]);
		idx++;
	}
}

static void	set_env(char **cmd_argv, char **env)
{
	int		i;
	int		j;

	i = 0;
	while (cmd_argv[i])
	{
		j = 0;
		if (cmd_argv[i][j] == '=')
		{
			printf("env: setenv %s: Invalid argument\n", cmd_argv[i]);
			exit(1);
		}
		while (cmd_argv[i][j] && cmd_argv[i][j] != '=')
			j++;
		if (cmd_argv[i][j] == '\0')
		{
			printf("env: %s: No such file or directory\n", cmd_argv[i]);
			exit(127);
		}
		i++;
	}
	list_env(env);
	list_shv(cmd_argv);
}

void	builtin_env(char **cmd_argv, char **env)
{
	int		cmd_argc;

	cmd_argc = cnt_line(cmd_argv);
	if (!cmd_argc)
		list_env(env);
	else
		set_env(cmd_argv, env);
	exit(0);
}
