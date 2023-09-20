/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/20 16:52:32 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char			*line;
	t_linked_list	*list;
	t_tree_node		*root;

	set_shell_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (line[0] == '\0')
		{
			free(line);
			continue;
		}
		if (line)
		{
			add_history(line);
			list = lexer(line);
			free(line);
			root = parser(list); //check_syntax_errror
			free_list(list);
			//execve()
			free_tree(root);
			line = 0;
		}
		else
			return (ctrl_d());
	}
	return (0);
}
