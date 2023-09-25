/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex)get_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:36:51 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/25 21:02:18 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	pid_t c;
// 	int	status;

// 	c = fork();
// 	if (c == 0)
// 	{
// 		exit(13);
// 		execve("ls", argv, envp);
// 	}
// 	else
// 	{
// 		waitpid(c, &status, 0);
// 		char *input = readline("input> ");
// 		if (!strcmp(input, "$?"))
// 			printf("%d\n", WEXITSTATUS(status));
// 	}
// 	return (0);
// }