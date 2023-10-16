/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:06:44 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/16 12:29:47 by jaehyji          ###   ########.fr       */
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

static void env_stderror_print(char *argv, int error_code)
{
	write(2, "env: ", 6);
	if (error_code == 1)
	{
		write(2, "setenv ", 8);
		write(2, argv, ft_strlen(argv));
		write(2, ": ", 2);
		write(2, "Invalid argument", 17);
	}
	else
	{
		write(2, argv, ft_strlen(argv));
		write(2, ": ", 2);
		write(2, "No such file or directory", 17);
	}
	write(2, "\n", 1);
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
			env_stderror_print(cmd_argv[i], 1);
			exit_status = 1;
		}
		while (cmd_argv[i][j] && cmd_argv[i][j] != '=')
			j++;
		if (cmd_argv[i][j] == '\0')
		{
			env_stderror_print(cmd_argv[i], 127);
			exit_status = 127;
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
	exit_status = 0;
}
