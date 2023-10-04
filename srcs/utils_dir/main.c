/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/04 17:13:58 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line;
	char *heredoc;
	// t_linked_list *list;
	// t_tree_node *root;
	pid_t child;

	while (1)
	{
		set_shell_signal();
		line = readline("minishell$ ");
		if (line && line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (line)
		{
			if (!strcmp(line, "cat"))
			{
				set_blocking_signal();
				child = fork();
				if (child == 0)
					execve("cat", 0, 0);
				else
					wait(0);
			}
			else if (!strcmp(line, "heredoc"))
			{
				set_heredoc_signal();
				child = fork();
				if (child == 0)
				{
					set_fork_heredoc_signal();
					heredoc = readline("> ");
					while (heredoc)
					{
						free(heredoc);
						heredoc = readline("> ");
					}
					exit(0);
				}
				else
					wait(0);
			}
		}
		// if (line)
		// {
		// 	// add_history(line);
		// 	// list = lexer(line);
		// 	// free(line);
		// 	// line = 0;
		// 	// if (list == 0)
		// 	// 	continue ;
		// 	// root = parser(list); // check_syntax_errror
		// 	// if (root == 0)
		// 	// 	continue ;
		// 	// free_list(list);
		// 	// // execve()
		// 	// free_tree(root);
		// }
		else
			return (shell_ctrl_d());
	}
}
