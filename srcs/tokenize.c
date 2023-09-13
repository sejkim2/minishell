/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:19:56 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/13 16:03:06 by sejkim2          ###   ########.fr       */
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

static	void	init_token(t_token *token, t_symbol symbol, char *value)
{
	token->symbol = symbol;
	token->value = value;
}

static	t_token	*make_token(t_symbol symbol, char *value)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (new_token == 0)
		return (0);
	init_token(new_token, symbol, value);
	return (new_token);
}

t_token_node	*make_node(t_token *token)
{
	int				i;
	t_token_node	*new_node;

	i = 0;
	new_node = (t_token_node *)malloc(sizeof(t_token_node));
	if (new_node == 0)
		return (0);
	new_node->token = token;
	new_node->next = 0;
	return (new_node);
}

static int check_is_single_quote(char ch)
{
	if (ch == '\'')
		return (1);
	else
		return (0);
}

static int check_is_double_quote(char ch)
{
	if (ch == '\"')
		return (1);
	else
		return (0);
}

static int check_is_white_space(char ch)
{
	if (ch == '\t' || ch == ' ')
		return (1);
	else
		return (0);
}

static int check_is_meta_character(char ch)
{
	if (ch == '<' || ch == '>' || ch == '|' || ch == '&' || ch == '(' || ch == ')')
		return (1);
	else
		return (0);
}

static int check_is_seperator(char ch)
{
	if (check_is_white_space(ch) || check_is_meta_character(ch))
		return (1);
	else
		return (0);
}

// static char *make_value(char *cmd_line, int start, int end)
// {
// 	char *dest;

// 	dest = (char *)malloc(sizeof(char) * (end - start + 2));
// 	ft_strlcpy(dest, cmd_line + start, (end - start + 2));
// 	return (dest);
// }

static char *make_value(char *cmd_line, int start, int end)
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

t_token_node	*tokenize(char *cmd_line, int *index)
{
	char *value;
	int end;
	t_symbol symbol;

	end = *index;
	if (cmd_line[*index] == '<' || cmd_line[*index] == '>')
	{
		end++;
		// <<here + (redir, pipe, andif, orif, lbra, rbra, whitespace)
		if (cmd_line[*index] == cmd_line[*index + 1])
			end++;
		while (cmd_line[end] && check_is_white_space(cmd_line[end]))
			end++;
		while (cmd_line[end])
		{
			if (check_is_single_quote(cmd_line[end]))
			{
				end++;
				while (cmd_line[end] && !check_is_single_quote(cmd_line[end]))
					end++;
				if (!check_is_single_quote(cmd_line[end]))
				{
					printf("syntax!\n");
					exit(1);	//syntax error
				}
				end++;
			}
			else if (check_is_double_quote(cmd_line[end]))
			{
				end++;
				while (cmd_line[end] && !check_is_double_quote(cmd_line[end]))
					end++;
				if (!check_is_double_quote(cmd_line[end]))
				{
					printf("syntax!\n");
					exit(1);	//syntax error
				}
				end++;
			}
			else if (check_is_seperator(cmd_line[end]))
				break;
			else
				end++;
		}
		symbol = REDIRECTION;
	}
	else if (cmd_line[*index] == '|')
	{
		end++;
		if (cmd_line[*index] == cmd_line[*index + 1])
		{	
			end++;
			symbol = OR_IF;
		}
		else
			symbol = PIPE;
	}
	else if (cmd_line[*index] == '&')
	{
		end++;
		if (cmd_line[*index] == cmd_line[*index + 1])
		{
			end++;
			symbol = AND_IF;
		}
		else
		{
			printf("syntax!\n");
			exit(1); // syntax error
		}
	}
	else if (cmd_line[*index] == '=')
	{
		end++;
		symbol = EQUAL;
	}
	else if (cmd_line[*index] == '(')
	{
		end++;
		symbol = L_BRA;
	}
	else if (cmd_line[*index] == ')')
	{
		end++;
		symbol = R_BRA;
	}
	else
	{
		//word + (redi, pipe, andif, orif, equal, lbra, rbra, whitespace)
		while (cmd_line[end])
		{
			if (check_is_single_quote(cmd_line[end]))
			{
				end++;
				while (cmd_line[end] && !check_is_single_quote(cmd_line[end]))
					end++;
				if (!check_is_single_quote(cmd_line[end]))
				{
					printf("syntax!\n");
					exit(1);	//syntax error
				}
				end++;
			}
			else if (check_is_double_quote(cmd_line[end]))
			{
				end++;
				while (cmd_line[end] && !check_is_double_quote(cmd_line[end]))
					end++;
				if (!check_is_double_quote(cmd_line[end]))
				{
					printf("syntax!\n");
					exit(1);	//syntax error
				}
				end++;
			}
			else if (check_is_seperator(cmd_line[end]))
				break;
			else
				end++;
		}
		symbol = WORD;
	}
	value = make_value(cmd_line, *index, end);
	t_token *new_token = make_token(symbol, value);
	*index = end;
	return (make_node(new_token));
}
