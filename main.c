/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/24 18:26:38 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		root = parser(list);
		if (root == 0)
			return (line);
		run_root(root, env);
		unlink_tmpfile(root, 0);
	}
	else
		shell_ctrl_d();
	return (line);
}

int	main(void)
{
	char	**env;
	char	*line;
	int		o_fd[2];

	env = init_setting(environ, o_fd);
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
