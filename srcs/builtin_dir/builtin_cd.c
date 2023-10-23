/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:28:08 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/23 16:06:41 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_argc(char **env)
{
	char	*path;

	path = get_envval("HOME", env);
	if (path && chdir(path) == -1)
	{
		free(path);
		ft_stderror_print("cd", NULL, "HOME not set");
		g_exit_status = 1;
	}
	if (path)
		free(path);
}

static void	yes_argc(char *path, char **env)
{
	if (chdir(path) == -1)
	{
		ft_stderror_print("cd", path, strerror(errno));
		g_exit_status = 1;
	}
}

void	builtin_cd(char **cmd_argv, char **env)
{
	char	buff[PATH_MAX];
	int		cmd_argc;

	g_exit_status = 0;
	cmd_argc = cnt_line(cmd_argv);
	if (!cmd_argc)
		no_argc(env);
	else
		yes_argc(*cmd_argv, env);
}
