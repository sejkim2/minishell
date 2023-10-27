/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:54:42 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/27 12:53:32 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int signum)
{
	(void)signum;
	write(2, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 1;
}

void	set_shell_signal(void)
{
	set_terminal_print_off();
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

int	shell_ctrl_d(void)
{
	write(2, "exit\n", 5);
	set_terminal_print_on();
	return (0);
}
