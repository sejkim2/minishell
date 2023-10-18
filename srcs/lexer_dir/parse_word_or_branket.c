/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word_or_branket.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:40:01 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/18 15:53:20 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// word + (redi, pipe, andif, orif, equal, lbra, rbra, whitespace)
int	parse_word(char *cmd_line, int *end, t_token *token)
{
	int	start;

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
	token->str_info = make_quote_string(cmd_line, start, *end);
	token->symbol = WORD;
	return (1);
}

int	parse_branket(char ch, int *end, t_token *token)
{
	(*end)++;
	if (ch == '(')
		token->symbol = L_BRA;
	else
		token->symbol = R_BRA;
	return (1);
}
