/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:42:37 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/22 12:26:59 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**init_environ(char **envp)
{
	int		cnt;
	char	**environ;

	cnt = cnt_line(envp);
	environ = (char **)malloc(sizeof(char *) * (cnt + 1));
	environ[cnt] = 0;
	matrix_cpy(envp, environ);
	return (environ);
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
			env_val = get_envval(str[1], env);
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

char	**add_env(char *av, char **env)
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
	renv[j] = av;
	renv[j + 1] = NULL;
	return (renv);
}
