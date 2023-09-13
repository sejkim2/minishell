/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:06:44 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/13 19:42:39 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	list_env(char **envp)
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

int	set_env(char **argv, char **envp)
{
	while
	argv[i][j]
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1 || strcmp(argv[1], "env"))
		return (printf("error\n"));
	if (argc == 2)
		return (list_env(envp));
	else
		return (set_env(argv + 2, envp));
}
