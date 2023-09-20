/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:47:00 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/20 17:03:45 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
