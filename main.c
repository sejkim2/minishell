/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/24 11:30:37 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_linked_list	*list;
	t_tree_node		*root;
	char			**env;
	char			*line;
	int				o_fd[2];

	env = init_environ(environ);
	store_std_fd(o_fd);
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
			run_root(root, &env, o_fd);
			// free_list(list);
			// free_tree(root);
			recover_std_fd(o_fd);
		}
		else
			return (shell_ctrl_d());
	}
}
