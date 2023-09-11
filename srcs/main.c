/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/11 14:03:19 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_signal_number = 0;
pid_t child;

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_linked_list	*list;
	struct termios	origin;

	origin = terminal_option();
	set_shell_signal();
	while (1)
	{
		if (g_signal_number != 0)
			g_signal_number = set_shell_signal();
		line = readline("minishell-1.0$ ");
		if (line)
		{
			if (!strcmp(line, "cat"))
			{
				child = fork();
				if (child == 0)
				{
					set_blocking_signal();
					int fd = open("test", O_RDWR);
					dup2(fd, 1);
					execve("cat", argv, envp);
				}
				else
				{
					g_signal_number = check_blocking_signal();
					wait(0);
				}
			}
			add_history(line);
			list = lexer(line);
			free_list(list);
			line = 0;
		}
		else
			return (shell_ctrl_d());
	}
}
