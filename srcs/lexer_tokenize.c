/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:09:15 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/21 16:27:20 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// < in1
//1. redir	: redir(<, <<, >, >>) + remove_white_space() + word
//2. pipe	: pipe(|)
//3. and_if : and_if(&&)
//4. or_if	: or_if(||)
//5. equal	: equal(=)
//6. l_bra	: l_bra(()
//7. r_bra	: r_bra())
//8. word : case1 : single_quote or double_quote
//			case2 : other

/*
	<
	<""
	구별
*/

// <<here + (redir, pipe, andif, orif, lbra, rbra, whitespace)
static	t_symbol	parse_redirection__(char *cmd_line, int cur_index, int *end)
{
	(*end)++;
	if (!cmd_line[*end])
		print_unexpected_token_syntax_error('\n');
	if (cmd_line[cur_index] == '<' && cmd_line[*end] == '>')
		print_unexpected_token_syntax_error('\n');
	if (cmd_line[cur_index] == '>' && cmd_line[*end] == '<')
		print_unexpected_token_syntax_error('<');
	if (cmd_line[cur_index] == cmd_line[cur_index + 1])
		(*end)++;
	return (parse_redirection(cmd_line, end));
}

t_token_node	*tokenize(char *cmd_line, int *index)
{
	char		*value;
	t_token		*new_token;
	int			end;
	t_symbol	symbol;

	end = *index;
	if (cmd_line[*index] == '<' || cmd_line[*index] == '>')
		symbol = parse_redirection__(cmd_line, *index, &end);
	else if (cmd_line[*index] == '|' || cmd_line[*index] == '&')
		symbol = parse_pipe_or_orif_or_andif(cmd_line, cmd_line[*index], &end);
	else if (cmd_line[*index] == '(' || cmd_line[*index] == ')')
		symbol = parse_branket(cmd_line[*index], &end);
	else
		symbol = parse_word(cmd_line, &end);
	value = make_value(cmd_line, *index, end);
	new_token = make_token(symbol, value);
	*index = end;
	return (make_node(new_token));
}
