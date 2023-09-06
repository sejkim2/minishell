/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_character_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:19:06 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/06 17:27:33 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_is_meta_character(char *cmd_line, int index)
{
	char	ch;

	ch = cmd_line[index];
	if (ch == '&' || ch == '|' \
	|| ch == '<' || ch == '>' \
	|| ch == '(' || ch == ')' \
	|| ch == '$')
		return (1);
	else
		return (0);
}

int	check_is_quote(char *cmd_line, int index)
{
	char	ch;

	ch = cmd_line[index];
	if (ch == '\'' || ch == '\"')
		return (1);
	else
		return (0);
}

int	check_is_white_space(char *cmd_line, int index)
{
	char	ch;

	ch = cmd_line[index];
	if (ch == ' ' || ch == '\t' || ch == '\n')
		return (1);
	else
		return (0);
}

int	check_is_seperator(char *cmd_line, int index)
{
	if (check_is_meta_character(cmd_line, index) \
	|| check_is_quote(cmd_line, index) \
	|| check_is_white_space(cmd_line, index))
		return (1);
	else
		return (0);
}
