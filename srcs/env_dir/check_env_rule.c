/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_rule.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:28:19 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/31 20:09:24 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_dup(char *str, char *env_name, char **env)
{
	int		i;
	char	*compare;

	i = 0;
	while (env[i])
	{
		compare = get_envname(env[i]);
		if (!ft_strcmp(env_name, compare))
		{
			free(compare);
			if (ft_strchr(str, '='))
			{
				free_str(env[i]);
				env[i] = ft_strdup(str);
			}
			return (1);
		}
		free_str(compare);
		i++;
	}
	return (0);
}

static int	check_key_string(char *str)
{
	int		idx;
	char	let;

	idx = 1;
	while (str[idx] && str[idx] != '=')
	{
		let = str[idx];
		if (!ft_isalpha(let))
			if (!ft_isdigit(let))
				return (0);
		idx++;
	}
	return (1);
}

static char	**add_export(char *str, char **env)
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
		renv[j] = ft_strdup(env[i]);
		i++;
		j++;
	}
	renv[j] = ft_strdup(str);
	renv[j + 1] = NULL;
	free_arr(env);
	return (renv);
}

static char	**check_equation(char *str, char **env)
{
	char	*env_name;

	env_name = get_envname(str);
	if (!check_dup(str, env_name, env))
		env = add_export(str, env);
	free_str(env_name);
	return (env);
}

int	check_key_rule(char **cmd_argv, char ***env)
{
	int		idx;
	int		flag;
	char	f_let;

	idx = 0;
	while (cmd_argv[idx])
	{
		flag = 0;
		f_let = cmd_argv[idx][0];
		if (!(f_let == '_'))
			if (!ft_isalpha(f_let))
				flag = 1;
		if (!check_key_string(cmd_argv[idx]))
			flag = 1;
		if (flag == 1)
			ft_stderror_print("export", cmd_argv[idx], \
			"not a valid identifier");
		else
			*env = check_equation(cmd_argv[idx], *env);
		idx++;
	}
	return (flag);
}
