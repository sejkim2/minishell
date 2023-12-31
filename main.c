/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/11/03 14:23:54 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	print_ascii_banner(void)
{
	printf("******************************************************\n");
	printf("**⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣤⣶⣶⣾⣿⣿⣿⣿⣿⣷⣶⣶⣶⣤⣀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀**\n");
	printf("**⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣶⣿⣿⣿⡿⠿⠿⠛⠛⠛⠛⠛⠛⠛⠛⠿⠿⠿⣿⣿⣿⣿⣶⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀**\n");
	printf("**⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣾⣿⣿⠿⠛⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠙⠻⢿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀**\n");
	printf("**⠀⠀⠀⠀⠀⠀⠀⣠⣾⣿⣿⠟⠋⠁⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⢀⡤⠶⠤⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⢿⣿⣿⣷⣄⠀⠀⠀⠀⠀⠀ **\n");
	printf("**⠀⠀⠀⠀⢠⣾⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⣿⠀⠠⢤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢻⣿⣿⣧⡄⠀⠀⠀⠀ **\n");
	printf("**⠀⠀⠀⢰⣿⣿⣟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠛⠛⠛⠘⠦⠤⠼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢘⣿⣿⣿⠆⠀⠀⠀ **\n");
	printf("**               minishell_ver_3.0                  **\n");
	printf("**⣶⣶⣶⣶⣶⣶⣶⣶⣶⡆⢰⣶⣶⡆⠀⢰⣶⣶⡆⠀⢰⣶⣶⡆⠀⢰⣶⣶⡆⠀⢲⣶⣶⣄⠀⠀⠀⢰⣶⣶⠀⠀⣶⣶⣶⣶⣶⣶⣶⣶**\n");
	printf("**⠉⠉⠉⢹⣿⣿⠉⠉⠉⠁⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⢸⣿⣿⣿⣦⡀⠀⢸⣿⣿⠀⠀⣿⣿⣏⡉⠉⠉⠉⠉**\n");
	printf("**⠀⠀⠀⢸⣿⣿⠀⠀⠀⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⢸⣿⣿⣿⣿⣷⣄⢸⣿⣿⠀⠀⠙⠿⣿⣿⣶⣄⠀⠀**\n");
	printf("**⠀⠀⠀⢸⣿⣿⠀⠀⠀⠀⠸⣿⣿⣇⠀⣸⣿⣿⣇⠀⣸⣿⣿⠇⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠙⣿⣿⣿⣿⣿⠀⠀⠀⠀⠈⠙⠿⣿⣿⣦**\n");
	printf("**⠀⠀⠀⢸⣿⣿⠀⠀⠀⠀⠀⠘⢿⣿⣷⣿⡿⢿⣿⣷⣿⡿⠋⠀⠀⢸⣿⣿⡇⠀⢸⣿⣿⡇⠀⠈⢻⣿⣿⣿⠀⠀⣤⣤⣤⣤⣤⣿⣿⣿**\n");
	printf("**⠀⠀⠀⠸⠿⠿⠀⠀⠀⠀⠀⠀⠀⠻⠿⠟⠁⠀⠻⠿⠟⠁⠀⠀⠀⠸⠿⠿⠃⠀⠸⠿⠿⠃⠀⠀⠀⠙⠿⠿⠀⠀⠿⠿⠿⠿⠿⠿⠿ **\n");
	printf("******************************************************\n");
}

char	*read_command_line(char ***env)
{
	char			*line;
	t_linked_list	*list;
	t_tree_node		*root;

	line = readline("minishell$ ");
	if (line)
	{
		add_history(line);
		list = lexer(line);
		if (list == 0)
			return (line);
		root = parser(list, *env);
		if (root == 0)
			return (line);
		free_list(list, 0);
		run_root(root, env);
		free_tree(root, 1);
	}
	else
		shell_ctrl_d();
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;
	char	*line;
	int		o_fd[2];

	(void)argc;
	(void)argv;
	print_ascii_banner();
	env = init_setting(envp, o_fd);
	while (1)
	{
		set_shell_signal();
		line = read_command_line(&env);
		if (line)
			free(line);
		else
			break ;
		recover_std_fd(o_fd);
	}
	return (0);
}
