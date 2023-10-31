/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 10:54:15 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/31 12:32:52 by jaehyji          ###   ########.fr       */
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
	while (path[i])
	{
		cmd_with_path = ft_strjoin(path[i], cmd_with_root);
		if (!cmd_with_path)
			malloc_error();
		if (access(cmd_with_path, X_OK) == 0)
		{
			free(cmd_with_root);
			return (cmd_with_path);
		}
		free(cmd_with_path);
		i++;
	}
	free(cmd_with_root);
	return (input_cmd);
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
		res = ft_strdup(cmd);
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
