/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:32:26 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/16 15:16:23 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(int i, char *env_name, char *env_val, char **env)
{
	int		j;

	j = 0;
	write(1, "declare -x ", 12);
	write(1, env_name, ft_strlen(env_name));
	if (is_equal(env[i]))
	{
		write(1, "=\"", 2);
		while (env_val[j])
		{
			if (env_val[j] == '\"' || env_val[j] == '$')
				write(1, "\\", 1);
			write(1, &env_val[j], 1);
			j++;
		}
		write(1, "\"", 1);
	}
	printf("\n");
}

void	list_export(char **env)
{
	int		cnt;
	int		i;
	char	*env_name;
	char	*env_val;

	cnt = cnt_line(env);
	sort_ascii(env, cnt);
	i = 0;
	while (i < cnt)
	{
		env_name = get_envname(env[i]);
		env_val = get_envval(env_name, env);
		print_export(i, env_name, env_val, env);
		free_2str(env_name, env_val);
		i++;
	}
	exit_status = 0;
}

char	**add_export(char *str, char **env)
{
	int		i;
	int		j;
	int		cnt;
	char	**renv;

	i = 0;
	j = 0;
	cnt = cnt_line(env);
	renv = (char **)malloc(sizeof(char *) * (cnt + 2));
	while (i < cnt)
	{
		renv[j] = env[i];
		i++;
		j++;
	}
	renv[j] = str;
	renv[j + 1] = NULL;
	return (renv);
}

void	set_export(char **cmd_argv, char **env)
{
	check_key_rule(cmd_argv, &env);
	list_export(env);
}

void	builtin_export(char **cmd_argv, char **env)
{
	int		cmd_argc;

	cmd_argc = cnt_line(cmd_argv);
	if (!cmd_argc)
		list_export(env);
	else
		set_export(cmd_argv, env);
}
