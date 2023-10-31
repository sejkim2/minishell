/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:28:08 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/31 20:05:36 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	re_path(char **env, char *type, char *path)
{
	int		idx;
	char	*envname;
	char	*tmp;

	idx = 0;
	while (env[idx])
	{
		envname = ft_strnstr(env[idx], type, ft_strlen(type));
		if (!envname)
			idx++;
		else
		{
			free_str(env[idx]);
			tmp = ft_strjoin(type, path);
			if (!tmp)
				malloc_error();
			env[idx] = tmp;
			break ;
		}
	}
}

static void	no_argc(char **env)
{
	char	*path;
	char	buff[PATH_MAX];

	path = get_envval("HOME", env);
	if ((chdir(path) == -1))
	{
		ft_stderror_print("cd", NULL, "HOME not set");
		g_exit_status = 1;
	}
	else
	{	
		getcwd(buff, PATH_MAX);
		re_path(env, "PWD=", buff);
	}
	free_str(path);
}

static void	yes_argc(char *path, char **env)
{
	char	buff[PATH_MAX];

	if (chdir(path) == -1)
	{
		ft_stderror_print("cd", path, strerror(errno));
		g_exit_status = 1;
	}
	else
	{	
		getcwd(buff, PATH_MAX);
		re_path(env, "PWD=", buff);
	}
}

void	builtin_cd(char **cmd_argv, char **env)
{
	int		cmd_argc;
	char	buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	re_path(env, "OLDPWD=", buff);
	g_exit_status = 0;
	cmd_argc = cnt_line(cmd_argv);
	if (!cmd_argc)
		no_argc(env);
	else
		yes_argc(*cmd_argv, env);
}
