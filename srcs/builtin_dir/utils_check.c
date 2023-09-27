/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:28:19 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/27 15:55:28 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key_rule(char **av, char ***env)
{
	int		idx;
	int		flag;
	char	let;

	idx = 0;
	while (av[idx])
	{
		flag = 0;
		let = av[idx][0];
		if (!(let == '_' \
		|| ('A' <= let && let <= 'Z') || ('a' <= let && let <= 'z')))
			flag = 1;
		if (!check_key_string(av[idx]))
			flag = 1;
		if (flag == 1)
			printf("minishell: export: `%s': not a valid identifier\n", av[idx]);
		else
			*env = check_equation(av[idx], *env);
		idx++;
	}
	return (flag);
}

int	check_key_string(char *av)
{
	int		idx;
	char	let;

	idx = 1;
	while (av[idx] && av[idx] != '=')
	{
		let = av[idx];
		if (!(('A' <= let && let > 'Z') || ('a' <= let && let <= 'z') \
		|| let == '_' || ('0' <= let && let <= '9')))
			return (0);
		idx++;
	}
	return (1);
}

int	is_equal(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

char	**check_equation(char *av, char **env)
{
	char	*env_name;
	char	*env_val;

	env_name = get_envname(av);
	env_val = get_envval(env_name, env);
	if (!check_dup(av, env_name, env))
	{
		free_2str(env_name, env_val);
		return (add_export(av, env));
	}
	return (env);
}

int	check_dup(char *av, char *env_name, char **env)
{
	int		i;
	char	*compare;

	i = 0;
	while (env[i])
	{
		compare = get_envname(env[i]);
		if (!strcmp(env_name, compare))
		{
			free(compare);
			if (is_equal(av))
				env[i] = av;
			return (1);
		}
		free(compare);
		i++;
	}
	return (0);
}
