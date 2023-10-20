/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:54:15 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/20 15:03:11 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*check_cmd_is_availabe(char **path, char *input_cmd)
{
	int		i;
	char	*cmd_with_root;
	char	*cmd_with_path;

	i = 0;
	cmd_with_root = ft_strjoin("/", input_cmd);
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
	int		root_place;
	char	*res;

	root_place = find_root(cmd);
	if (root_place > 0)
	{
		if (access(cmd, X_OK) == -1)
			res = 0;
		else
			res = ft_strdup(cmd);
	}
	else
		res = check_cmd_is_availabe(path, cmd);
	return (res);
}

char	*init_path_env(char *cmd, char **path)
{
	char	*res;

	res = init_path_env_utils(cmd, path);
	return (res);
}