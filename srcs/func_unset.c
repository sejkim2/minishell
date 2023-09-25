/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:42:03 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/19 15:47:16 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**rearrange_env(int cnt, char **env)
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
	return (renv);
}

void	func_unset(char **argv, char **env)
{
	int		i;
	int		j;
	int		cnt;
	char	*env_name[2];

	i = 0;
	cnt = cnt_line(env);
	while (argv[i])
	{
		j = 0;
		while (env[j])
		{
			env_name[0] = get_envname(argv[i]);
			env_name[1] = get_envname(env[j]);
			if (!strcmp(env_name[0], env_name[1]))
			{
				env[j] = 0;
				break ;
			}
			j++;
		}
		free_2str(env_name[0], env_name[1]);
		i++;
	}
	env = rearrange_env(cnt, env);
}
