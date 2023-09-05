/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_and_lexer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:48:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/05 09:39:35 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_token(t_token *token, t_type check_type, char *value)
{
	token->token_type = check_type;
	token->token_value = value;
}

static t_token	*make_token(t_type check_type, char *value)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		exit(1);
	init_token(new_token, check_type, value);
	return (new_token);
}

static t_token_node *make_node(char *cmd_line, int start, int end, t_type check_type)
{
    char *value;
    int i;
    t_token_node *new_node;

    //strdup로 수정 예정
    value = (char *)malloc(sizeof(char) * (end - start + 2));
    i = 0;
    new_node = (t_token_node *)malloc(sizeof(t_token_node));
    /* check null safety */
    
    while (start <= end)
        value[i++] = cmd_line[start++];
    value[i] = '\0';
    new_node->token = make_token(check_type, value);
    new_node->next = 0;
    return (new_node);
}

static t_linked_list *make_list(void)
{
    t_linked_list *new_list;

    new_list = (t_linked_list *)malloc(sizeof(t_linked_list));
    new_list->num_of_node = 0;
    new_list->head = 0;
    new_list->tail = 0;
    return (new_list);
}

static void push_back_list(t_linked_list *list, t_token_node *node)
{
    if (list->num_of_node == 0)
        list->head = node;
    else
        list->tail->next = node;
    list->tail = node;
    list->num_of_node++;
}

static int check_is_meta_character(char *cmd_line, int index)
{
    char ch;

    ch = cmd_line[index];
    if (ch == '&'|| ch == '|' \
    || ch == '<' || ch == '>' \
    || ch == '(' || ch == ')')
        return (1);
    else
        return (0);
}

static int check_is_quote(char *cmd_line, int index)
{
    char ch;

    ch = cmd_line[index];
    if (ch == '\'' || ch == '\"')
        return (1);
    else
        return (0);
}

static int check_is_white_space(char *cmd_line, int index)
{
    char ch;

    ch = cmd_line[index];
    if (ch == ' ' || ch == '\t' || ch == '\n')
        return (1);
    else
        return (0);
}

static int check_is_seperator(char *cmd_line, int index)
{
    if (check_is_meta_character(cmd_line, index) \
        || check_is_quote(cmd_line, index) \
        || check_is_white_space(cmd_line, index))
        return (1);
    else
        return (0);
}

static void set_double_meta_character(char ch, t_type *token_type)
{
    if (ch == '&')
        *token_type = AND_IF;
    else if (ch == '|')
        *token_type = OR_IF;
    else if (ch == '<')
        *token_type = HEREDOC;
    else
        *token_type = APPEND;
}

static void set_single_meta_character(char ch, t_type *token_type)
{
    if (ch == '&')
        *token_type = WORD;
    else if (ch == '|')
        *token_type = PIPE;
    else if (ch == '<')
        *token_type = IN_REDIRECTION;
    else if (ch == '>')
        *token_type = OUT_REDIRECTION;
    else if (ch == '(')
        *token_type = LEFT_BLANKET;
    else
        *token_type = RIGHT_BLANKET;
}

static void set_other_character(char ch, t_type *token_type)
{
    if (ch == '\'')
        *token_type = SINGLE_QUOTE;
    else if (ch == '\"')
        *token_type = DOUBLE_QUOTE;
    else
        *token_type = DOLLOR_SIGN;
}

static void set_token_type(char *cmd_line, int index, t_type *token_type)
{
    char ch;

    ch = cmd_line[index];
    if (check_is_meta_character(cmd_line, index))
    {
        if ((cmd_line[index] == cmd_line[index + 1]) && (cmd_line[index] != '(' && cmd_line[index] != ')'))
            set_double_meta_character(ch, token_type);
        else
            set_single_meta_character(ch, token_type);
    }
    else
        set_other_character(ch, token_type);
}

/* lexical analysis */
t_linked_list *lexer(char *cmd_line)
{
    int i;
    int start;
    t_type token_type;
    t_linked_list *list;

    i = 0;
    start = 0;
    token_type = WORD;
    list = make_list();
    
    while (cmd_line[i])
    {
        while (cmd_line[i] && check_is_white_space(cmd_line, i))
            i++;
        if (!cmd_line[i])
            break;
        start = i;
        if (check_is_meta_character(cmd_line, i) || check_is_quote(cmd_line, i))
        {
            set_token_type(cmd_line, i, &token_type);
            if (token_type == AND_IF || token_type == OR_IF || token_type == HEREDOC || token_type == APPEND)
            {
                push_back_list(list, make_node(cmd_line, start, start + 1, token_type));
                i = i + 2;
            }
            else
            {
                push_back_list(list, make_node(cmd_line, start, start, token_type));
                i = i + 1;
            }
        }
        else
        {
            while (cmd_line[i] && !check_is_seperator(cmd_line, i))
                i++;
            token_type = WORD;
            push_back_list(list, make_node(cmd_line, start, i - 1, token_type));
        }
    }

    t_token_node *cur = list->head;
    while (cur)
    {
        printf("[ token : %s type : %d]\n", cur->token->token_value, cur->token->token_type);
        cur = cur->next;
    }
    return (list);
}