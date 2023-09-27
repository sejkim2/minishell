/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:36:51 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/27 12:50:21 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	main(int exit_code)
// {
// 	pid_t c;
// 	int	status;

// 	c = fork();
// 	if (c == 0)
// 		exit(exit_code);
// 	else
// 	{
// 		waitpid(c, &status, 0);
// 		printf("%d\n", WEXITSTATUS(status));
// 	}
// }