/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/11 11:32:35 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void print_banner(void)
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
	print_banner();
	char *line;
	t_linked_list *list;
	t_tree_node *root;

	while (1)
	{
		set_shell_signal();
		line = readline("minishell$ ");
		if (line)
		{
			if (line[0] == '\0')
			{
				free(line);
				continue;
			}
			add_history(line);
			list = lexer(line);
			free(line);
			if (list == 0)
				continue ;
			root = parser(list); // check_syntax_errror
			if (root == 0)
				continue ;
			tree_traverse(root, 0);
			// free_list(list);
			run_exec(root);
			// free_tree(root);
		}
		else
			return (shell_ctrl_d());
	}
}
