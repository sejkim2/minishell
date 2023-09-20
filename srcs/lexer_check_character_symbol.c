/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check_character_symbol.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:07:22 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/20 13:42:12 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_is_single_quote(char ch)
{
	if (ch == '\'')
		return (1);
	else
		return (0);
}

int check_is_double_quote(char ch)
{
	if (ch == '\"')
		return (1);
	else
		return (0);
}

int check_is_white_space(char ch)
{
	if (ch == '\t' || ch == ' ')
		return (1);
	else
		return (0);
}

int check_is_meta_character(char ch)
{
	if (ch == '<' || ch == '>' || ch == '|' || ch == '&' || ch == '(' || ch == ')')
		return (1);
	else
		return (0);
}

int check_is_seperator(char ch)
{
	if (check_is_white_space(ch) || check_is_meta_character(ch))
		return (1);
	else
		return (0);
}
