/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/25 20:59:34 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void print_ascii_banner(void)
{
	printf("******************************************************\n");
	printf("**⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣤⣶⣶⣾⣿⣿⣿⣿⣿⣷⣶⣶⣶⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀**\n");
	printf("**⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⣿⣿⣿⡿⠿⠿⠛⠛⠛⠛⠛⠛⠛⠛⠿⠿⠿⣿⣿⣿⣿⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀**\n");
	printf("**⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣾⣿⣿⠿⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠻⢿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀**\n");
	printf("**⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⠟⠋⠁⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⢀⡤⠶⠤⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⢿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀ **\n");
	printf("**⠀⠀⠀⠀⢠⣾⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⣿⠀⠠⢤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢻⣿⣿⣧⡄⠀⠀⠀⠀ **\n");
	printf("**⠀⠀⠀⢰⣿⣿⣟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠛⠘⠦⠤⠼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢘⣿⣿⣿⠆⠀⠀⠀ **\n");
	printf("**                minishell_ver_1.0                 **\n");
	printf("**⣶⣶⣶⣶⣶⣶⣶⣶⣶⡆⢰⣶⣶⡆⠀⢰⣶⣶⡆⠀⢰⣶⣶⡆⠀⢰⣶⣶⡆⠀⢲⣶⣶⣄⠀⠀⠀⢰⣶⣶⠀⠀⣶⣶⣶⣶⣶⣶⣶⣶**\n");
	printf("**⠉⠉⠉⢹⣿⣿⠉⠉⠉⠁⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⢸⣿⣿⣿⣦⡀⠀⢸⣿⣿⠀⠀⣿⣿⣏⡉⠉⠉⠉⠉**\n");
	printf("**⠀⠀⠀⢸⣿⣿⠀⠀⠀⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⢸⣿⣿⣿⣿⣷⣄⢸⣿⣿⠀⠀⠙⠿⣿⣿⣶⣄⠀⠀**\n");
	printf("**⠀⠀⠀⢸⣿⣿⠀⠀⠀⠀⠸⣿⣿⣇⠀⣸⣿⣿⣇⠀⣸⣿⣿⠇⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠙⣿⣿⣿⣿⣿⠀⠀⠀⠀⠈⠙⠿⣿⣿⣦**\n");
	printf("**⠀⠀⠀⢸⣿⣿⠀⠀⠀⠀⠀⠘⢿⣿⣷⣿⡿⢿⣿⣷⣿⡿⠋⠀⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⠈⢻⣿⣿⣿⠀⠀⣤⣤⣤⣤⣤⣿⣿⣿**\n");
	printf("**⠀⠀⠀⠸⠿⠿⠀⠀⠀⠀⠀⠀⠀⠻⠿⠟⠁⠀⠻⠿⠟⠁⠀⠀⠀⠸⠿⠿⠃⠀⠸⠿⠿⠃⠀⠀⠀⠙⠿⠿⠀⠀⠿⠿⠿⠿⠿⠿⠿ **\n");
	printf("******************************************************\n");
}

int main(void)
{
	print_ascii_banner();
	char *line;
	t_linked_list *list;
	t_tree_node *root;

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
			if (list == 0)
			{
				free(line);
				continue ;
			}
			if (list->num_of_node == 0)
			{
				// free_list(list);
				free(line);
				continue ;
			}
			free(line);
			root = parser(list); // check_syntax_errror
			if (root == 0)
			{
				// free_list(list);
				free(line);
				continue ;
			}
			// execve()
			// free_list(list);
			// free_tree(root);
			line = 0;
		}
		else
			return (shell_ctrl_d());
	}
}
