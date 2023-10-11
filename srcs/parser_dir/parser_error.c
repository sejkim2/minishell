/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 13:32:50 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/06 14:31:52 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_error(char *error_string)
{
	if (error_string == 0)
		printf("minishell: parse error near unexpected token `newline\'\n");
	else
		printf("minishell: parse error near unexpected token `%s\'\n", \
		error_string);
	return (-1);
}
