/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:49:39 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/28 14:43:38 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**rearrange_env(int cnt, char **env)
{
	int		i;
	int		j;
	int		size;
	char	**renv;

	i = 0;
	j = 0;
	size = cnt_size(env, cnt);
	renv = (char **)malloc(sizeof(char *) * (size + 1));
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

int	check_unset_key_string(char *argv)
{
	int		idx;
	char	let;

	idx = 1;
	while (argv[idx] && argv[idx] != '=')
	{
		let = argv[idx];
		if (!ft_isalpha(let))
			if (!ft_isdigit(let))
				return (0);
		idx++;
	}
	return (1);
}

int	check_unset_key_rule(char *argv)
{
	int		flag;

	flag = 0;
	if (ft_strchr(argv, '='))
		flag = 1;
	if (!(argv[0] == '_'))
		if (!ft_isalpha(argv[0]))
			flag = 1;
	if (!check_unset_key_string(argv))
		flag = 1;
	if (flag == 1)
		ft_stderror_print("unset", argv, "not a valid identifier");
	return (flag);
}

int	cnt_size(char **env, int cnt)
{
	int		idx;
	int		ret;

	idx = 0;
	ret = 0;
	while (idx < cnt)
	{
		if (!env[idx])
		{
			idx++;
			continue ;
		}
		idx++;
		ret++;
	}
	return (ret);
}

void	compare_envname(char *unset_name, char ***env, int cnt)
{
	char	*env_name;
	int		j;

	j = 0;
	while (j < cnt)
	{
		if (!(*env)[j])
		{
			j++;
			continue ;
		}
		env_name = get_envname((*env)[j]);
		if (!ft_strcmp(env_name, unset_name))
		{
			free((*env)[j]);
			(*env)[j] = 0;
		}
		free(env_name);
		j++;
	}
}
