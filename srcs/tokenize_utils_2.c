/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:40:59 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/19 15:10:08 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *make_value(char *cmd_line, int start, int end)
{
	char *new_string;
	int i;

	new_string = malloc(sizeof(char) * (end - start + 1));
	i = 0;
	while (start < end)
	{
		if (check_is_single_quote(cmd_line[start]))
		{
			start++;
			while (!check_is_single_quote(cmd_line[start]))
				new_string[i++] = cmd_line[start++];
			start++;
		}
		else if (check_is_double_quote(cmd_line[start]))
		{
			start++;
			while (!check_is_double_quote(cmd_line[start]))
				new_string[i++] = cmd_line[start++];
			start++;
		}
		else
			new_string[i++] = cmd_line[start++];
	}
	new_string[i] = '\0';
	return (new_string);
}

void parse_single_quote_string(char *cmd_line, int *end)
{
	(*end)++;
	while (cmd_line[*end] && !check_is_single_quote(cmd_line[*end]))
		(*end)++;
	if (!check_is_single_quote(cmd_line[*end]))
	{
		printf("lexer error!\n");
		exit(1);
	}
	(*end)++;
}

void parse_double_quote_string(char *cmd_line, int *end)
{
	(*end)++;
	while (cmd_line[*end] && !check_is_double_quote(cmd_line[*end]))
		(*end)++;
	if (!check_is_double_quote(cmd_line[*end]))
	{
		printf("lexer error!\n");
		exit(1);
	}
	(*end)++;
}
