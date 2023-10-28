/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:42:38 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/28 20:50:32 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_env_dup(char **env, char **cmd_argv)
{
	int		i;
	int		j;
	char	*s1;
	char	*s2;

	i = 0;
	j = 0;
	while (cmd_argv[i])
	{
		s1 = get_envname(cmd_argv[i]);
		while (env[j])
		{
			s2 = get_envname(env[j]);
			if (ft_strcmp(s1, s2))
				printf("%s\n", env[j]);
			free(s2);
			j++;
		}
		free(s1);
		i++;
	}
}

void	env_argv_error(char *argv, int error_code)
{
	write(2, "env: ", 6);
	if (error_code == 1)
	{
		write(2, "setenv ", 8);
		write(2, argv, ft_strlen(argv));
		write(2, ": ", 3);
		write(2, "Invalid argument", 17);
	}
	else
	{
		write(2, argv, ft_strlen(argv));
		write(2, ": ", 3);
		write(2, "No such file or directory", 26);
	}
	write(2, "\n", 2);
}

int	check_dup_envname(char *s1, char *s2)
{
	char	*envname1;
	char	*envname2;

	envname1 = get_envname(s1);
	envname2 = get_envname(s2);
	if (!ft_strcmp(envname1, envname2))
	{
		free_2str(envname1, envname2);
		return (1);
	}
	free_2str(envname1, envname2);
	return (0);
}

char	**check_argv_dup(char **cmd_argv)
{
	int		i;
	int		j;
	int		cnt;

	cnt = cnt_line(cmd_argv);
	if (cnt == 1)
		return (cmd_argv);
	i = 0;
	while (i < cnt - 1)
	{
		j = i + 1;
		while (j < cnt)
		{
			if (check_dup_envname(cmd_argv[i], cmd_argv[j]))
			{
				free(cmd_argv[i]);
				cmd_argv[i] = NULL;
				break ;
			}
			j++;
		}
		i++;
	}
	return (rearrange_env(cnt, cmd_argv));
}
