/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:47:00 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/21 15:15:13 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_unexpected_token_syntax_error(char ch)
{
	if (ch == '\n')
		printf("minishell: syntax error near unexpected token `newline\'\n");	
	else
		printf("minishell: syntax error near unexpected token `%c\'\n", ch);
	exit(258);
}

void	lexer_error(void)
{
	printf("lexer error!\n");
	exit(1);
}

void	malloc_error(void)
{
	printf("malloc error!\n");
	exit(1);
}
