/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:40:01 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/20 12:23:18 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_symbol parse_redirection(char *cmd_line, int *end)
{
	while (cmd_line[*end] && check_is_white_space(cmd_line[*end]))
		(*end)++;
	if (!cmd_line[*end])
	{
		printf("lexer error!\n");
		exit(1);
	}
	if (cmd_line[*end] == '(' || cmd_line[*end] == ')' || cmd_line[*end] == '<' || cmd_line[*end] == '>')
	{
		printf("lexer error!\n");
		exit(1);
	}
	while (cmd_line[*end])
	{
		if (check_is_single_quote(cmd_line[*end]))
			parse_single_quote_string(cmd_line, end);
		else if (check_is_double_quote(cmd_line[*end]))
			parse_double_quote_string(cmd_line, end);
		else if (check_is_seperator(cmd_line[*end]))
			break;
		else
			(*end)++;
	}
	return (REDIRECTION);
}

t_symbol parse_word(char *cmd_line, int *end)
{
	// word + (redi, pipe, andif, orif, equal, lbra, rbra, whitespace)
	while (cmd_line[*end])
	{
		if (check_is_single_quote(cmd_line[*end]))
			parse_single_quote_string(cmd_line, end);
		else if (check_is_double_quote(cmd_line[*end]))
			parse_double_quote_string(cmd_line, end);
		else if (check_is_seperator(cmd_line[*end]))
			break;
		else
			(*end)++;
	}
	return (WORD);
}

t_symbol parse_equal_or_branket(char ch, int *end)
{
	(*end)++;

	if (ch == '=')
		return (EQUAL);
	else if (ch == '(')
		return (L_BRA);
	else	//ch == ')'
		return (R_BRA);
}

t_symbol parse_pipe_or_orif_or_andif(char *cmd_line, char ch, int *end)
{
	(*end)++;
	if (!cmd_line[*end])
	{
		printf("lexer error!\n");
		exit(1);
	}
	if (ch == '|')
	{
		if (ch == cmd_line[*end])
		{	
			(*end)++;
			if (!cmd_line[*end])
			{
				printf("lexer error!\n");
				exit(1);
			}
			return (OR_IF);
		}
		else
			return (PIPE);
	}
	else //ch == '&'
	{
		if (ch == cmd_line[*end])
		{
			(*end)++;
			if (!cmd_line[*end])
			{
				printf("lexer error\n");
				exit(1);
			}
			return (AND_IF);
		}
		else
		{
			printf("lexer error!\n");
			exit(1);
		}
	}
}