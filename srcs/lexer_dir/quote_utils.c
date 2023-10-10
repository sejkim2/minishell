/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:07 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/06 14:10:08 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_close_quote(char *cmd_line, int index, char quote)
{
	index++;
	while (cmd_line[index])
	{
		if (cmd_line[index] == quote)
			break ;
		index++;
	}
	if (cmd_line[index] == quote)
		return (1);
	else
		return (0);
}

void	single_close_quote(char *cmd_line, int *start, int end)
{
	(*start)++;
	while (*start < end && !check_is_single_quote(cmd_line[*start]))
		(*start)++;
	(*start)++;
}

void	double_close_quote(char *cmd_line, int *start, int end)
{
	(*start)++;
	while (*start < end && !check_is_double_quote(cmd_line[*start]))
		(*start)++;
	(*start)++;
}

void	normal_string(char *cmd_line, int *start, int end)
{
	while (*start < end)
	{
		if (check_is_single_quote(cmd_line[*start]) \
		&& check_is_close_quote(cmd_line, *start, '\''))
			break ;
		if (check_is_double_quote(cmd_line[*start]) \
		&& check_is_close_quote(cmd_line, *start, '\"'))
			break ;
		(*start)++;
	}
}

int	count_quote_string(char *cmd_line, int start, int end)
{
	int	cnt_string;

	cnt_string = 0;
	while (start < end)
	{
		if (check_is_single_quote(cmd_line[start]) && \
		check_is_close_quote(cmd_line, start, '\''))
			single_close_quote(cmd_line, &start, end);
		else if (check_is_double_quote(cmd_line[start]) \
		&& check_is_close_quote(cmd_line, start, '\"'))
			double_close_quote(cmd_line, &start, end);
		else
			normal_string(cmd_line, &start, end);
		cnt_string++;
	}
	return (cnt_string);
}
