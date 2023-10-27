/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:47:00 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/27 18:23:49 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_unexpected_token_syntax_error(char *error_string, char error_ch)
{
	if (error_string == 0)
	{
		if (error_ch == '\n')
			ft_putstr_fd("minishell: syntax error near \
		unexpected token `newline\'\n", 2);
		else
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putchar_fd(error_ch, 2);
			ft_putstr_fd("\'\n", 2);
		}
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(error_string, 2);
		ft_putstr_fd("\'\n", 2);
	}
	return (-1);
}

int	print_unmatched_parentheses_syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error unmatched parentheses\n", 2);
	return (-1);
}

int	print_arithmetic_expansion_syntax_error(void)
{
	ft_putstr_fd("minishell: syntax error arithmetic expansion\n", 2);
	return (-1);
}

void	malloc_error(void)
{
	ft_putstr_fd("malloc error!\n", 2);
	exit(0);
}

void	system_call_error(void)
{
	ft_putstr_fd("system call error!\n", 2);
	exit(0);
}
