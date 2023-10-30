/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:51:50 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/28 17:20:39 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_ascii(char **envp, int cnt)
{
	char	*a;
	char	*b;
	int		i;
	int		j;

	while (cnt--)
	{
		i = 0;
		while (envp[i] && envp[i + 1])
		{
			j = 0;
			while (envp[i][j] == envp[i + 1][j])
				j++;
			if (envp[i][j] > envp[i + 1][j])
			{
				a = envp[i];
				b = envp[i + 1];
				envp[i] = b;
				envp[i + 1] = a;
			}
			i++;
		}
	}
}

void	print_export(int i, char *env_name, char *env_val, char **env)
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
	write(1, "\n", 1);
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
	g_exit_status = 0;
}
