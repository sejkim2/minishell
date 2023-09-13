/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:32:26 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/13 18:07:47 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cnt_line(char **str_arr)
{
	int		cnt;

	cnt = 0;
	while (str_arr[cnt])
		cnt++;
	return (cnt);
}

void	sort_ascii(char **envp, int cnt)
{
	char	*a;
	char	*b;
	int		i;
	int		j;

	while (cnt--)
	{
		i = 0;
		while (envp[i] && envp[i + 1])
		{
			j = 0;
			while (envp[i][j] == envp[i + 1][j])
				j++;
			if (envp[i][j] > envp[i + 1][j])
			{
				a = envp[i];
				b = envp[i + 1];
				envp[i] = b;
				envp[i + 1] = a;
			}
			i++;
		}
	}
}

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
		while (envp[idx][eql] != '=')
			eql++;
		env_name = ft_substr(envp[idx], 0, eql);
		printf("declare -x %s=\"%s\"\n", env_name, getenv(env_name));
		free(env_name);
		idx++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1 || strcmp(argv[1], "export"))
		return (printf("error\n"));
	if (argc == 2)
		return (list_export(envp));
}
