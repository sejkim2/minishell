/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:13:28 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/06 14:13:39 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_single_quote_string(char *cmd_line, int *end)
{
	if (check_is_close_quote(cmd_line, *end, '\''))
	{
		(*end)++;
		while (cmd_line[*end] && !check_is_single_quote(cmd_line[*end]))
			(*end)++;
		(*end)++;
	}
	else
	{
		(*end)++;
		while (cmd_line[*end] && !check_is_double_quote(cmd_line[*end]) \
		&& !check_is_seperator(cmd_line[*end]))
			(*end)++;
	}
}

void	parse_double_quote_string(char *cmd_line, int *end)
{
	if (check_is_close_quote(cmd_line, *end, '\"'))
	{
		(*end)++;
		while (cmd_line[*end] && !check_is_double_quote(cmd_line[*end]))
			(*end)++;
		(*end)++;
	}
	else
	{
		(*end)++;
		while (cmd_line[*end] && !check_is_single_quote(cmd_line[*end]) \
		&& !check_is_seperator(cmd_line[*end]))
			(*end)++;
	}
}
