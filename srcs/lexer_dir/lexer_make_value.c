/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_make_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:40:59 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/25 20:36:20 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	make_string_single_quote(char *cmd_line, \
char *new_string, int *start, int *index)
{
	if (check_is_close_quote(cmd_line, *start, '\''))
	{
		(*start)++;
		while (!check_is_single_quote(cmd_line[*start]))
			new_string[(*index)++] = cmd_line[(*start)++];
		(*start)++;
	}
	else
	{
		while (cmd_line[*start] && (!check_is_seperator(cmd_line[*start]) \
		&& !check_is_double_quote(cmd_line[*start])))
			new_string[(*index)++] = cmd_line[(*start)++];
		if (check_is_white_space(cmd_line[*start]))
			(*start)++;
	}
}

static	void	make_string_double_quote(char *cmd_line, \
char *new_string, int *start, int *index)
{
	if (check_is_close_quote(cmd_line, *start, '\"'))
	{
		(*start)++;
		while (!check_is_double_quote(cmd_line[*start]))
			new_string[(*index)++] = cmd_line[(*start)++];
		(*start)++;
	}
	else
	{
		while (cmd_line[*start] && (!check_is_seperator(cmd_line[*start]) \
		&& !check_is_single_quote(cmd_line[*start])))
			new_string[(*index)++] = cmd_line[(*start)++];
		if (check_is_white_space(cmd_line[*start]))
			(*start)++;
	}
}

char	*make_value(char *cmd_line, int start, int end)
{
	char	*new_string;
	int		i;

	new_string = malloc(sizeof(char) * (end - start + 1));
	if (new_string == 0)
		malloc_error();
	i = 0;
	while (start < end)
	{
		if (check_is_single_quote(cmd_line[start]))
			make_string_single_quote(cmd_line, new_string, &start, &i);
		else if (check_is_double_quote(cmd_line[start]))
			make_string_double_quote(cmd_line, new_string, &start, &i);
		else
			new_string[i++] = cmd_line[start++];
	}
	new_string[i] = '\0';
	return (new_string);
}
