/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:42:03 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/16 12:20:55 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**rearrange_env(int cnt, char **env)
{
	int		i;
	int		j;
	char	**renv;

	i = 0;
	j = 0;
	renv = (char **)malloc(sizeof(char *) * (cnt + 1));
	while (i < cnt)
	{
		if (!env[i])
		{
			i++;
			continue ;
		}
		renv[j] = env[i];
		i++;
		j++;
	}
	renv[j] = NULL;
	free(env);
	return (renv);
}

void	builtin_unset(char **cmd_argv, char **env)
{
	int		i;
	int		j;
	int		cnt;
	char	*env_name[2];

	cnt = cnt_line(env);
	i = 0;
	while (cmd_argv[i])
	{
		j = 0;
		while (env[j])
		{
			env_name[0] = get_envname(cmd_argv[0]);
			env_name[1] = get_envname(env[j]);
			if (!strcmp(env_name[0], env_name[1]))
				env[j] = 0;
			j++;
		}
		i++;
		free_2str(env_name[0], env_name[1]);
	}
	env = rearrange_env(cnt, env);
	exit_status = 0;
}
