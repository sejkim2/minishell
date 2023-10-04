/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:06:44 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/27 15:47:32 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	list_env(char **envp)
{
	int		idx;

	idx = 0;
	while (envp[idx])
	{
		printf("%s\n", envp[idx]);
		idx++;
	}
	return (0);
}

static int	set_env(char **argv, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '=')
		{
			printf("env: setenv %s: Invalid argument\n", argv[i]);
			exit(1);
		}
		while (argv[i][j] && argv[i][j] != '=')
			j++;
		if (argv[i][j] == '\0')
		{
			printf("env: %s: No such file or directory\n", argv[i]);
			exit(127);
		}
		i++;
	}
	return (list_env(envp), list_env(argv));
}

// int	main(int argc, char **argv, char **envp)
// {
// 	if (argc == 1 || strcmp(argv[1], "env"))
// 		return (printf("error\n"));
// 	if (argc == 2)
// 		return (list_env(envp));
// 	else
// 		return (set_env(argv + 2, envp));
// }
