/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path_env-1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:54:15 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/13 20:15:17 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*check_cmd_is_availabe(char **path, char *input_cmd)
{
	int		i;
	char	*cmd_with_root;
	char	*cmd_with_path;

	i = 0;
	cmd_with_root = ft_strjoin("/", input_cmd);	//    /ls
	free(input_cmd);
	while (path[i])
	{
		cmd_with_path = ft_strjoin(path[i], cmd_with_root);
		if (access(cmd_with_path, X_OK) == 0)
		{
			free(cmd_with_root);
			return (cmd_with_path);
		}
		free(cmd_with_path);
		i++;
	}
	printf("pipex: command not found: %s\n", input_cmd);
	free(cmd_with_root);
	return (0);
}

static	int	find_root(char *cmd)
{
	int	i;

	i = ft_strlen(cmd);
	while (i >= 0)
	{
		if (cmd[i] == '/')
			return (i + 1);
		i--;
	}
	return (0);
}

static	char	*init_path_env_utils(char *cmd, char **path)
{
	int	root_place;
	char *res;

	root_place = find_root(cmd);
	//경로가 있는 경우
	if (root_place > 0)
	{
		if (access(cmd, X_OK) == -1)
		{
			res = 0;
			printf("pipex: %s: %s\n", strerror(errno), cmd);
		}
		else
			res = ft_strdup(cmd);
	}
	//경로가 없는 경우
	else
		res = check_cmd_is_availabe(path, cmd);
	return (res);
}

char	*init_path_env(char *cmd, char **path)
{
	char *res;

	if (cmd == 0)
	{
		res = 0;
		printf("pipex: permission denied:\n");
	}
	else
		res = init_path_env_utils(cmd, path);
	return (res);
}
