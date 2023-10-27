/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:32:50 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/27 16:12:31 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_error(char *error_string)
{
	if (error_string == 0)
		printf("minishell: syntax error near unexpected token `newline\'\n");
	else
		printf("minishell: syntax error near unexpected token `%s\'\n", \
		error_string);
	return (-1);
}
