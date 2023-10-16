/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stderror_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:50:04 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/16 18:04:37 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_stderror_print(char *cmd, char *argv, char *err_string)
{
	write(2, "minishell: ", 12);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 3);
	if (argv)
	{
		if (!ft_strncmp(cmd, "export", 6))
			write(2, "`", 2);
		write(2, argv, ft_strlen(argv));
		if (!ft_strncmp(cmd, "export", 6))
			write(2, "\'", 2);
		write(2, ": ", 3);
	}
	write(2, err_string, ft_strlen(err_string));
	write(2, "\n", 1);
	exit_status = 1;
}
