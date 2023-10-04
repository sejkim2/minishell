/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/27 19:35:44 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line;
	t_linked_list *list;
	t_tree_node *root;

	set_shell_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (line && line[0] == '\0')
		{
			free(line);
			continue;
		}
		if (line)
		{
			add_history(line);
			list = lexer(line);
			free(line);
			line = 0;
			if (list == 0)
				continue ;
			root = parser(list); // check_syntax_errror
			if (root == 0)
				continue ;
			free_list(list);
			// execve()
			free_tree(root);
		}
		else
			return (shell_ctrl_d());
	}
}
