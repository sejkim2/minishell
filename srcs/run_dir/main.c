/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/17 11:37:16 by jaehyji          ###   ########.fr       */
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
	while (1)
	{
		exit_status = 0;
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
			// tree_traverse(root, 0);
			// free_list(list);
			run_root(root, &env);
			// free_tree(root);
		}
		else
			return (shell_ctrl_d());
	}
}
