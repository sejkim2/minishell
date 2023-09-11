/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/11 17:31:39 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*line;
	t_linked_list	*list;
	struct termios	origin;
	char			*h_line;
	int				cursor;
	pid_t child;

	origin = terminal_option();
	while (1)
	{
		set_shell_signal(&cursor);
		line = readline("minishell-1.0$ ");
		if (line)
		{
			if (!strcmp(line, "cat"))
			{
				child = fork();
				if (child == 0)
				{
					set_blocking_signal();
					execve("cat", argv, envp);
				}
				else
				{
					check_blocking_signal();
					wait(0);
				}
			}
			if (!strcmp(line, "<< heredoc"))
			{
				child = fork();
				set_heredoc_signal();
				if (child == 0)
				{
					while (1)
					{
						h_line = readline("> ");
						if (!h_line)
						{
							printf("\033[1A");
							printf("\033[2C");
							exit(0);
						}
						// pipe 혹은 임시파일에 데이터 저장
						free(h_line);
					}
				}
				else
				{
					check_heredoc_signal(&cursor);
					wait(0);
				}
			}
			tcsetattr(1, 0, &origin);
			add_history(line);
			list = lexer(line);
			free_list(list);
			line = 0;
		}
		else
			return (shell_ctrl_d(cursor));
	}
}
