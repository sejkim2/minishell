/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:42:37 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/14 20:03:55 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**init_environ(char **envp)
{
	int		cnt;
	char	**environ;

	cnt = 0;
	while (envp[cnt])
		cnt++;
	environ = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!environ)
		exit(1);
	environ[cnt] = 0;
	matrix_cpy(envp, environ);
	return (environ);
}

char	*get_env(char *env_name, char **env)
{
	int		i;
	int		j;
	char	*rstr;


	i = 0;
	while (env[i])
	{
		j = 0;
		if (!strncmp(env_name, env[i], ft_strlen(env_name)))
		{
			while (env[i][j] != '=')
				j++;
			rstr = ft_substr(env[i], j + 1, ft_strlen(env[i]));
			return (rstr);
		}
		i++;
	}
	return (0);
}

char	**change_env(char **av, char **env)
{
	int		i;
	int		j;
	char	*env_val;
	char	*str[3];

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j] && av[i][j] != '$')
			j++;
		if (av[i][j] == '$')
		{
			make_str(i, j, av, str);
			env_val = get_env(str[1], env);
			if (env_val)
				str[2] = env_val;
			else
				str[2] = ft_strdup("");
			av[i] = ft_strjoin(str[0], str[2]);
			free_2str(str[0], str[2]);
		}
		i++;
	}
	return (av);
}

char	**rearrange_env(int cnt, char **env)
{
	int		i;
	int		j;
	char	**renv;

	i = 0;
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
	free(env);
	renv[j] = NULL;
	return (renv);
}
