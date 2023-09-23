/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:40:01 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/22 15:03:11 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_symbol	parse_redirection(char *cmd_line, int *end, int **bit_mask)
{
	int start;

	while (cmd_line[*end] && check_is_white_space(cmd_line[*end]))
		(*end)++;
	if (!cmd_line[*end])
		print_unexpected_token_syntax_error('\n');
	if (cmd_line[*end] == '(' || cmd_line[*end] == ')' \
	|| cmd_line[*end] == '<' || cmd_line[*end] == '>' \
	|| cmd_line[*end] == '&' || cmd_line[*end] == '|')
		print_unexpected_token_syntax_error(cmd_line[*end]);
	start = *end;
	while (cmd_line[*end])
	{
		if (check_is_single_quote(cmd_line[*end]))
			parse_single_quote_string(cmd_line, end);
		else if (check_is_double_quote(cmd_line[*end]))
			parse_double_quote_string(cmd_line, end);
		else if (check_is_seperator(cmd_line[*end]))
			break ;
		else
			(*end)++;
	}
	*bit_mask = make_bit_mask(cmd_line, start, *end);
	return (REDIRECTION);
}

int count_dollor_sign(char *cmd_line, int start, int end)
{
	int cnt_dollor;

	cnt_dollor = 0;
	while (start < end)
	{
		if (cmd_line[start] == '$')
		{
			cnt_dollor++;
			while (start < end && (cmd_line[start] == '$'))
				start++;
		}
		else
			start++;
	}
	return (cnt_dollor);
}

int *make_bit_mask(char *cmd_line, int start, int end)
{
	int cnt_dollor;
	int *dollor_bit_mask;
	int i;

	cnt_dollor = count_dollor_sign(cmd_line, start, end);
	i = 0;
	if (cnt_dollor == 0)
		return (0);
	dollor_bit_mask = malloc(sizeof(int) * (cnt_dollor + 1));
	while (i < cnt_dollor)
		dollor_bit_mask[i++] = 0;
	dollor_bit_mask[i] = -1;
	i = 0;
	while (start < end)
	{
		if (check_is_single_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\''))
		{
			start++;
			while (start < end && !check_is_single_quote(cmd_line[start]))
			{
				if (cmd_line[start] == '$')
				{
					while (start < end && !check_is_white_space(cmd_line[start]) && !check_is_single_quote(cmd_line[start]))
						start++;
					i++;
				}
				else
					start++;
			}
			start++;
		}
		else if (check_is_double_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\"'))
		{
			start++;
			while (start < end && !check_is_double_quote(cmd_line[start]))
			{
				if (cmd_line[start] == '$')
				{
					while (start < end && !check_is_white_space(cmd_line[start]) && !check_is_double_quote(cmd_line[start]))
					{
						dollor_bit_mask[i] += 1;
						start++;
					}
					i++;
				}
				else
					start++;
			}
			start++;
		}
		else
		{
			if (cmd_line[start] == '$')
			{
				while (start < end)
				{
					if (check_is_single_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\''))
						break ;
					if (check_is_double_quote(cmd_line[start]) && check_is_close_quote(cmd_line, start, '\"'))
						break ;
					dollor_bit_mask[i] += 1;
					start++;
				}
				i++;
			}
			else
				start++;
		}
	}
	return (dollor_bit_mask);
}

// word + (redi, pipe, andif, orif, equal, lbra, rbra, whitespace)
t_symbol	parse_word(char *cmd_line, int *end, int **bit_mask)
{
	int start;

	start = *end;
	while (cmd_line[*end])
	{
		if (check_is_single_quote(cmd_line[*end]))
			parse_single_quote_string(cmd_line, end);
		else if (check_is_double_quote(cmd_line[*end]))
			parse_double_quote_string(cmd_line, end);
		else if (check_is_seperator(cmd_line[*end]))
			break ;
		else
			(*end)++;
	}
	*bit_mask = make_bit_mask(cmd_line, start, *end);
	return (WORD);
}

t_symbol	parse_branket(char ch, int *end)
{
	(*end)++;
	if (ch == '(')
		return (L_BRA);
	else
		return (R_BRA);
}

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
