/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:32:50 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/27 19:47:12 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_error(char *error_string)
{
	if (error_string == 0)
		ft_putstr_fd("minishell: syntax error near unexpected \
token `newline\'\n", 2);
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(error_string, 2);
		ft_putstr_fd("\'\n", 2);
	}
	return (-1);
}
