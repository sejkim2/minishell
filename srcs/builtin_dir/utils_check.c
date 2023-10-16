/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:28:19 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/16 15:12:20 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key_rule(char **cmd_argv, char ***env)
{
	int		idx;
	int		flag;
	char	let;

	idx = 0;
	while (cmd_argv[idx])
	{
		flag = 0;
		let = cmd_argv[idx][0];
		if (!(let == '_' \
		|| ('A' <= let && let <= 'Z') || ('a' <= let && let <= 'z')))
			flag = 1;
		if (!check_key_string(cmd_argv[idx]))
			flag = 1;
		if (flag == 1)
			ft_stderror_print("export", cmd_argv[idx], "not a valid identifier");
		else
			*env = check_equation(cmd_argv[idx], *env);
		idx++;
	}
	return (flag);
}

int	check_key_string(char *str)
{
	int		idx;
	char	let;

	idx = 1;
	while (str[idx] && str[idx] != '=')
	{
		let = str[idx];
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

char	**check_equation(char *str, char **env)
{
	char	*env_name;

	env_name = get_envname(str);
	if (!check_dup(str, env_name, env))
		env = add_export(str, env);
	free(env_name);
	return (env);
}

int	check_dup(char *str, char *env_name, char **env)
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
			if (is_equal(str))
				env[i] = str;
			return (1);
		}
		free(compare);
		i++;
	}
	return (0);
}
