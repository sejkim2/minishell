/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:47:00 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/26 16:41:12 by jaehyji          ###   ########.fr       */
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
			printf("minishell: syntax error near unexpected token `%c\'\n", \
			error_ch);
	}
	else
		printf("minishell: syntax error near unexpected token `%s\'\n", \
		error_string);
	return (-1);
}

int	print_unmatched_parentheses_syntax_error(void)
{
	printf("minishell: syntax error unmatched parentheses\n");
	return (-1);
}

int	print_arithmetic_expansion_syntax_error(void)
{
	printf("minishell: syntax error arithmetic expansion\n");
	return (-1);
}

void	malloc_error(void)
{
	printf("malloc error!\n");
	exit(0);
}

void	system_call_error(void)
{
	perror("system call error");
	exit(0);
}
