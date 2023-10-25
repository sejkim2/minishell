/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:58:12 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/25 19:34:56 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_record_status(void)
{
	int		status;

	g_exit_status = WEXITSTATUS(status);
	exit(g_exit_status);
}

void	wait_record_status(void)
{
	int		status;

	wait(&status);
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
