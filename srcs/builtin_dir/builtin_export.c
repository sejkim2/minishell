/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:32:26 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/23 18:23:55 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(int i, char *env_name, char *env_val, char **env)
{
	int		j;

	j = 0;
	write(1, "declare -x ", 11);
	write(1, env_name, ft_strlen(env_name));
	if (ft_strchr(env[i], '='))
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

static void	list_export(char **env)
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
	g_exit_status = 0;
}

void	builtin_export(char **cmd_argv, char ***env)
{
	int		cmd_argc;

	g_exit_status = 0;
	cmd_argc = cnt_line(cmd_argv);
	if (!cmd_argc)
		list_export(*env);
	else
		check_key_rule(cmd_argv, env);
}
