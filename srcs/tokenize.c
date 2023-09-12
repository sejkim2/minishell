/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:19:56 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/12 21:26:15 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static	void	set_double_meta_character(char ch, t_type *token_type)
// {
// 	if (ch == '&')
// 		*token_type = AND_IF;
// 	else if (ch == '|')
// 		*token_type = OR_IF;
// 	else if (ch == '<')
// 		*token_type = HEREDOC;
// 	else
// 		*token_type = APPEND;
// }

// static	void	set_single_meta_character(char ch, t_type *token_type)
// {
// 	if (ch == '&')
// 		*token_type = WORD;
// 	else if (ch == '|')
// 		*token_type = PIPE;
// 	else if (ch == '<')
// 		*token_type = IN_REDIRECTION;
// 	else if (ch == '>')
// 		*token_type = OUT_REDIRECTION;
// 	else if (ch == '(')
// 		*token_type = LEFT_BLANKET;
// 	else if (ch == ')')
// 		*token_type = RIGHT_BLANKET;
// 	else
// 		*token_type = DOLLOR_SIGN;
// }

// static	void	set_other_character(char ch, t_type *token_type)
// {
// 	if (ch == '\'')
// 		*token_type = SINGLE_QUOTE;
// 	else if (ch == '\"')
// 		*token_type = DOUBLE_QUOTE;
// 	else
// 		*token_type = DOLLOR_SIGN;
// }

// static	void	set_token_type(char *cmd_line, int index, t_type *token_type)
// {
// 	char	ch;

// 	ch = cmd_line[index];
// 	if (check_is_meta_character(cmd_line, index))
// 	{
// 		if ((cmd_line[index] == cmd_line[index + 1]) && \
// 		(cmd_line[index] != '(' && cmd_line[index] != ')'\
// 		&& cmd_line[index] != '$'))
// 			set_double_meta_character(ch, token_type);
// 		else
// 			set_single_meta_character(ch, token_type);
// 	}
// 	else
// 		set_other_character(ch, token_type);
// }

// static char *make_string(char *cmd_line, int start, int end)
// {
// 	char *dest;

// 	dest = (char *)malloc(sizeof(char) * (end - start + 2));
// 	ft_strlcpy(dest, cmd_line + start, (end - start + 2));
// 	return (dest);
// }

static void init_token(t_token token, t_symbol symbol, char *value)
{
	token.symbol = symbol;
	token.value = value;
}

static t_token_node *make_token_node(t_symbol symbol, char *value)
{
	t_token_node *new;

	new = malloc(sizeof(t_token_node));

}

static int check_is_r_bra(char ch)
{
	if (ch == ')')
		return (1);
	else
		return (0);
}

static int check_is_l_bra(char ch)
{
	if (ch == '(')
		return (1);
	else
		return (0);
}

static int check_is_equal(char ch)
{
	if (ch == '=')
		return (1);
	else
		return (0);
}

static int check_is_pipe(char ch)
{
	if (ch == '|')
		return (1);
	else
		return (0);
}

static int check_is_or_if(char ch, char next_ch)
{
	if (ch == '|' && next_ch == '|')
		return (1);
	else
		return (0);
}

static int check_is_and_if(char ch, char next_ch)
{
	if (ch == '&' && next_ch == '&')
		return (1);
	else
		return (0);
}


static int check_is_heredoc_or_append(char ch, char next_ch)
{
	if (ch == next_ch)
		return (1);
	else
		return (0);
}

static int check_is_redir(char ch)
{
	if (ch == '<' || ch == '>')
		return (1);
	else
		return (0);
}

//1. redir	: redir(<, <<, >, >>) + remove_white_space() + word
	//2. pipe	: pipe(|)
	//3. and_if : and_if(&&)
	//4. or_if	: or_if(||)
	//5. equal	: equal(=)
	//6. l_bra	: l_bra(()
	//7. r_bra	: r_bra())
	//8. word : case1 : single_quote or double_quote
	//			case2 : other

t_token_node	*minishell_tokenize(char *cmd_line, int *i)
{
	t_token_node *node;
	
	if (check_is_redir(cmd_line[*i]))
	{
		if (check_is_heredoc_or_append(cmd_line[*i], cmd_line[*i + 1]))
			return (make_node(make_token(cmd_line, *i, *i + 1, REDIRECTION)));
		else
			return (make_node(make_token(cmd_line, *i, *i, REDIRECTION)));
	}
	else if (check_is_and_if(cmd_line[*i], cmd_line[*i + 1]))
		return (make_node(make_value(cmd_line, *i, *i + 1, AND_IF)));
	else if (check_is_or_if(cmd_line[*i], cmd_line[*i + 1]))
		value = make_value(cmd_line, *i, *i + 1, OR_IF);
	else if (check_is_pipe(cmd_line[*i]))
		value = make_value(cmd_line, *i, *i, PIPE);
	else if (check_is_equal(cmd_line[*i]))
		value = make_value(cmd_line, *i, *i, EQUAL);
	else if (check_is_l_bra(cmd_line[*i]))
		value = make_value(cmd_line, *i, L_BRA);
	else if (check_is_r_bra(cmd_line[*i]))
		value = make_value(cmd_line, *i, R_BRA);
	else
		value = make_value(cmd_line, *i, WORD);
}
