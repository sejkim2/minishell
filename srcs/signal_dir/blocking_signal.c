/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocking_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:17:08 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/27 17:43:37 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	blocking_ctrl_c(int signum)
{
	(void)signum;
	g_exit_status = 130;
}

static void	blocking_ctrl_backslash(int signum)
{
	(void)signum;
	g_exit_status = 131;
}

void	set_blocking_signal(void)
{
	signal(SIGINT, blocking_ctrl_c);
	signal(SIGQUIT, blocking_ctrl_backslash);
}
