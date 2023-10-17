/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:06:44 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/17 13:11:27 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	인자 & 출력문 중북체크
*/

static void	check_env_dup(char **env, char **cmd_argv)
{
	int		i;
	int		j;
	char	*s1;
	char	*s2;

	i = 0;
	j = 0;
	while (cmd_argv[i])
	{
		s1 = get_envname(cmd_argv[i]);
		while (env[j])
		{
			s2 = get_envname(env[j]);
			if (strcmp(s1, s2))
				printf("%s\n", env[j]);
			free(s2);
			j++;
		}
		free(s1);
		i++;
	}
}

static void	list_env(char **env, char **cmd_argv)
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

static void env_stderror_print(char *argv, int error_code)
{
	write(2, "env: ", 6);
	if (error_code == 1)
	{
		write(2, "setenv ", 8);
		write(2, argv, ft_strlen(argv));
		write(2, ": ", 3);
		write(2, "Invalid argument", 17);
	}
	else
	{
		write(2, argv, ft_strlen(argv));
		write(2, ": ", 3);
		write(2, "No such file or directory", 26);
	}
	write(2, "\n", 2);
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
			return ;
		}
		while (cmd_argv[i][j] && cmd_argv[i][j] != '=')
			j++;
		if (cmd_argv[i][j] == '\0')
		{
			env_stderror_print(cmd_argv[i], 127);
			exit_status = 127;
			return ;
		}
		i++;
	}
	list_env(env, cmd_argv);
}

void	builtin_env(char **cmd_argv, char **env)
{
	int		cmd_argc;

	exit_status = 0;
	cmd_argc = cnt_line(cmd_argv);
	if (!cmd_argc)
		list_env(env, NULL);
	else
		set_env(cmd_argv, env);
}
