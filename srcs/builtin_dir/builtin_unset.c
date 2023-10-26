/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:42:03 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/26 16:10:28 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_unset(char **cmd_argv, char ***env)
{
	int		i;
	int		cnt;

	g_exit_status = 0;
	cnt = cnt_line(*env);
	i = 0;
	while (cmd_argv[i])
	{
		if (check_unset_key_rule(cmd_argv[i]))
		{
			i++;
			continue ;
		}
		compare_envname(cmd_argv[i], env, cnt);
		i++;
	}
	*env = rearrange_env(cnt, *env);
}
