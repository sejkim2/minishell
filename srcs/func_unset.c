/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:42:03 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/14 20:03:17 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	func_unset(char **argv, char **env)
{
	int		i;
	int		j;
	int		cnt;

	i = 0;
	cnt = cnt_line(env);
	while (argv[i])
	{
		j = 0;
		while (env[j])
		{
			if (!strncmp(argv[i], env[j], ft_strlen(argv[i])))
			{
				env[i] = 0;
				break ;
			}
			j++;
		}
		i++;
	}
	env = rearrange_env(env, cnt);
}
