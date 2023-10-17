/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:28:08 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/17 11:40:44 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	옵션없는 cd 구현.
	cd는 인자로 절대 & 상대 경로를 받음.
	경로가 여러개일 경우, 첫 번째 인자만 인자로 인정되고 다른 것들은 무시.
	첫 번째 인자의 옳고 그름만 따짐.
	Done.
*/

void	builtin_cd(char **cmd_argv, char **env)
{
	char	buff[PATH_MAX];
	int		cmd_argc;

	cmd_argc = cnt_line(cmd_argv);
	if (!cmd_argc)
	{
		if (chdir(get_envval("HOME", env)) == -1)
		{
			ft_stderror_print("cd", *cmd_argv, "HOME not set");
			exit_status = 1;
		}
	}
	else
	{
		if (chdir(*cmd_argv) == -1)
		{
			ft_stderror_print("cd", *cmd_argv, strerror(errno));
			exit_status = 1;
		}
	}
}
