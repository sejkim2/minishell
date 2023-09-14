/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:32:26 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/14 20:04:42 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	list_export(char **envp)
{
	int		cnt;
	int		idx;
	int		eql;
	char	*env_name;

	cnt = cnt_line(envp);
	idx = 0;
	sort_ascii(envp, cnt);
	while (idx < cnt)
	{
		eql = 0;
		if (!envp[idx])
		{
			idx++;
			continue ;
		}
		while (envp[idx][eql] != '=')
			eql++;
		env_name = ft_substr(envp[idx], 0, eql);
		printf("declare -x %s=\"%s\"\n", env_name, envp[idx] + eql);
		free(env_name);
		idx++;
	}
	return (0);
}

void	check_equation(char **argv)
{
	
}

int	set_env(char **argv, char **env)
{
	check_equation(argv);
	func_unset(argv, env);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	env = init_envrion(envp);
	if (argc == 1 || strcmp(argv[1], "export"))
		return (printf("error\n"));
	if (argc == 2)
		return (list_export(envp));
	else
		return (set_env(argv, env));
}
