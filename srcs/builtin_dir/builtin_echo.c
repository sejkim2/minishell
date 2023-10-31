/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:36:27 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/31 13:56:00 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_no_opt_print(int cmd_argc, char **cmd_argv)
{
	int		idx;

	if (cmd_argc == 0)
	{
		write(1, "\n", 1);
		return ;
	}
	idx = 0;
	while (idx < cmd_argc)
	{
		write(1, cmd_argv[idx], ft_strlen(cmd_argv[idx]));
		if (idx < cmd_argc - 1)
			write(1, " ", 1);
		idx++;
	}
	write(1, "\n", 1);
	return ;
}

static void	echo_opt_print(int cmd_argc, char **cmd_argv)
{
	int		idx;

	idx = 0;
	while (idx < cmd_argc)
	{
		write(1, cmd_argv[idx], ft_strlen(cmd_argv[idx]));
		if (idx < cmd_argc - 1)
			write(1, " ", 1);
		idx++;
	}
	return ;
}

static int	echo_opt_flag(char *str)
{
	int		idx;

	idx = 1;
	if (str[0] == '\0' || str[0] != '-')
		return (0);
	if (!str[idx])
		return (0);
	while (str[idx] && str[idx] == 'n')
		idx++;
	if (str[idx] != '\0')
		return (0);
	return (1);
}

static void	echo_opt(int cmd_argc, char **cmd_argv)
{
	int		i;
	int		j;

	if (echo_opt_flag(*cmd_argv))
	{
		i = 0;
		while (cmd_argv[i] && cmd_argv[i][0] == '-')
		{
			j = 1;
			if (!cmd_argv[i][j])
				break ;
			while (cmd_argv[i][j])
			{
				if (cmd_argv[i][j] == 'n')
					j++;
				else
					return (echo_opt_print(cmd_argc - i, cmd_argv + i));
			}
			i++;
		}
		return (echo_opt_print(cmd_argc - i, cmd_argv + i));
	}
	else
		return (echo_no_opt_print(cmd_argc, cmd_argv));
}

void	builtin_echo(char **cmd_argv)
{
	int		cmd_argc;

	g_exit_status = 0;
	cmd_argc = cnt_line(cmd_argv);
	if (!cmd_argc)
		echo_no_opt_print(cmd_argc, cmd_argv);
	else
		echo_opt(cmd_argc, cmd_argv);
}
