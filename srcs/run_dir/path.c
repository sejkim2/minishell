/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:32:51 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/13 20:15:45 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**find_path_in_envp_and_split(char **envp)
{
	int		i;
	int		flag;
	char	*p;

	i = 0;
	flag = 0;
	while (envp[i])
	{
		p = ft_strnstr(envp[i], "PATH=", 5);
		if (p != 0)
		{
			flag = 1;
			break ;
		}
		else
			i++;
	}
	if (flag == 0)
		return (0);
	return (ft_split(p + 5, ':'));
}

char	*get_path(char *exe)
{
	char	**path;
	char *res;

	path = find_path_in_envp_and_split(environ);
	if (path == 0)
	{
		printf("$PATH is not exist\n");
		exit(1);
	}
	res = 0;
	res = init_path_env(exe, path);
	return (0);
}
