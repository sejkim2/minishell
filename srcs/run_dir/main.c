/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/20 14:35:42 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_linked_list 	*list;
	t_tree_node 	*root;
	char			**env;
	char 			*line;

	env = init_environ(environ);
	exit_status = 0;
	while (1)
	{
		set_shell_signal();
		line = readline("minishell$ ");
		if (line)
		{
			if (line[0] == '\0')
			{
				free(line);
				continue ;
			}
			add_history(line);
			list = lexer(line);
			free(line);
			if (list == 0)
				continue ;
			root = parser(list);
			if (root == 0)
				continue ;
			get_heredoc(root, 0);
			// tree_traverse(root, 0);
			// free_list(list);
			// run_root(root, &env);
			// free_tree(root);
		}
		else
			return (shell_ctrl_d());
	}
}
