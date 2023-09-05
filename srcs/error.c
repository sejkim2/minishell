/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:41:07 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/05 09:48:43 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char *error_string, int code)
{
	write(2, "minishell: ", 8);
	write(2, error_string, ft_strlen(error_string));
	write(2, ": ", 2);
	write(2, errno, ft_strlen(errno));
	write(2, "\n", 1);
	open_close(info);
	exit(1);
}
