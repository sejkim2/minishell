/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:52:52 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/11 16:17:11 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char			*line;
	t_linked_list	*list;

	set_shell_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (line)
		{
			add_history(line);
			list = lexer(line);
			parser(list); //check_syntax_errror
			//execve()
			free_list(list);
			line = 0;
		}
		else
			return (ctrl_d());
	}
	return (0);
}
