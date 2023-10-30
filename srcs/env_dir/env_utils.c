/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:42:37 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/30 19:50:05 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_setting(char **envp, int *o_fd)
{
	int		cnt;
	char	**env;

	cnt = cnt_line(envp);
	env = (char **)malloc(sizeof(char *) * (cnt + 1));
	matrix_cpy(env, envp);
	store_std_fd(o_fd);
	g_exit_status = 0;
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
	if (!rstr)
		malloc_error();
	return (rstr);
}

char	*get_envval(char *env_name, char **env)
{
	int		idx[2];
	char	*str[2];

	idx[0] = 0;
	while (env[idx[0]])
	{
		idx[1] = 0;
		str[0] = get_envname(env[idx[0]]);
		if (!ft_strcmp(env_name, str[0]))
		{
			free(str[0]);
			if (!ft_strchr(env[idx[0]], '='))
				return (NULL);
			while (env[idx[0]][idx[1]] && env[idx[0]][idx[1]] != '=')
				idx[1]++;
			str[1] = ft_substr(env[idx[0]], idx[1] + 1, \
			ft_strlen(env[idx[0]]) - (idx[1] + 1));
			if (!str[1])
				malloc_error();
			return (str[1]);
		}
		free(str[0]);
		idx[0]++;
	}
	return (NULL);
}
