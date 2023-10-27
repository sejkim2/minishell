/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:58:12 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/27 19:45:38 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_signal_status(pid_t exe_fork)
{
	int		status;

	waitpid(exe_fork, &status, 0);
	if (isatty(0))
	{
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			write(2, "^C\n", 3);
			return ;
		}
		else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		{
			write(2, "^\\Quit: 3\n", 10);
			return ;
		}
	}
	g_exit_status = WEXITSTATUS(status);
}

void	exit_record_status(void)
{
	int		status;

	g_exit_status = WEXITSTATUS(status);
	exit(g_exit_status);
}

void	wait_record_status(pid_t pro)
{
	int		status;

	waitpid(pro, &status, 0);
	g_exit_status = WEXITSTATUS(status);
}

void	wait_last_command(pid_t c_pro)
{
	int		status;

	close(0);
	close(1);
	waitpid(c_pro, &status, 0);
	g_exit_status = WEXITSTATUS(status);
	while (1)
		if (wait(&status) == -1)
			break ;
}
