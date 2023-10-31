/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:06:44 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/31 14:24:37 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_error(char *error_str, int status)
{
	env_argv_error(error_str, status);
	g_exit_status = status;
}

void	list_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		write(1, env[i], ft_strlen(env[i]));
		write(1, "\n", 1);
		i++;
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
			print_env_error(cmd_argv[i], 1);
		while (cmd_argv[i][j] && cmd_argv[i][j] != '=')
			j++;
		if (cmd_argv[i][j] == '\0')
			print_env_error(cmd_argv[i], 127);
		i++;
	}
	cmd_argv = check_argv_dup1(cmd_argv, env);
	list_env(cmd_argv);
	free_arr(cmd_argv);
}

void	builtin_env(char **cmd_argv, char **env)
{
	int		cmd_argc;

	g_exit_status = 0;
	cmd_argc = cnt_line(cmd_argv);
	if (!cmd_argc)
		list_env(env);
	else
		set_env(cmd_argv, env);
}
