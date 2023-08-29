/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:48:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/08/29 20:25:33 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void init_token(t_token *token, char *type, char *value)
{
    token->type = ft_strdup(type);
    token->value = ft_strdup(value);
}

static t_token *make_token(char *type, char *value)
{
    t_token *new_token;

    new_token = (t_token *)malloc(sizeof(t_token));
    /* check null safety */
    init_token(new_token, type, value);
    return (new_token);
}

static t_token_node *make_node(char *type, char *value)
{
    t_token_node *new_node;

    new_node = (t_token_node *)malloc(sizeof(t_token_node));
    /* check null safety */
    new_node->token = make_token(type, value);
    new_node->next = 0;
    return (new_node);
}

static t_linked_list *make_list(void)
{
    t_linked_list *new_list;

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

static int check_is_heredoc_or_append_or_andif_or_orif(char ch)
{
    if (ch == '&')
        return (1);
    else if (ch == '|')
        return (2);
    else if (ch == '<')
        return (3);
    else if (ch == '>')
        return (4);
    else
        return (0);
}

static int check_is_meta_character(char ch)
{
    if (ch == '&'|| ch == '|' \
    || ch == '<' || ch == '>' \
    || ch == ')' || ch == '(')
        return (1);
    else
        return (0);
}

static int check_is_quote(char ch)
{
    if (ch == '\'' || ch == '\"')
        return (1);
    else
        return (0);
}

static int check_is_white_space(char ch)
{
    if (ch == ' ' || ch == '\t' || ch == '\n')
        return (1);
    else
        return (0);
}

static int check_is_seperator(char ch)
{
    if (check_is_meta_character(ch) || check_is_quote(ch) || \
        check_is_white_space(ch))
        return (1);
    else
        return (0);
}

/* lexical analysis */
t_list *tokenize(char *str)
{
    int i;
    t_list *list;
    t_token *token;
    char *cmd_line;
    int start;
    int end;

    i = 0;
    list = make_list();
    cmd_line = ft_strtrim(str);
    start = 0;
    end = 0;
    while (cmd_line[i])
    {
        
        
    }
}