/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:42:37 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/16 14:30:02 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_environ(char **envp)
{
	int		cnt;
	char	**env;

	cnt = cnt_line(envp);
	env = (char **)malloc(sizeof(char *) * (cnt + 1));
	env[cnt] = 0;
	matrix_cpy(envp, env);
	return (env);
}

char	*get_envname(char *av)
{
	int		idx;
	char	*rstr;

	idx = 0;
	while (av[idx] && av[idx] != '=')
		idx++;
	rstr = ft_substr(av, 0, idx);
	return (rstr);
}

char	*get_envval(char *env_name, char **env)
{
	int		i;
	int		j;
	char	*compare;
	char	*rstr;

	i = 0;
	while (env[i])
	{
		j = 0;
		compare = get_envname(env[i]);
		if (!strcmp(env_name, compare))
		{
			while (env[i][j] != '=')
				j++;
			rstr = ft_substr(env[i], j + 1, ft_strlen(env[i]));
			free(compare);
			return (rstr);
		}
		free(compare);
		i++;
	}
	return (NULL);
}
