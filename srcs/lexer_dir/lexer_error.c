/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:47:00 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/27 17:45:30 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_unexpected_token_syntax_error(char *error_string, char error_ch)
{
	if (error_string == 0)
	{
		if (error_ch == '\n')
			printf("minishell: syntax error near unexpected token `newline\'\n");
		else
			printf("minishell: syntax error near unexpected token `%c\'\n", error_ch);
	}
	else
		printf("minishell: syntax error near unexpected token `%s\'\n", error_string);
	return (-1);
}

void	malloc_error(void)
{
	printf("malloc error!\n");
	exit(1);
}
