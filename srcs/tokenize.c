/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:48:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/08/28 15:47:38 by sejkim2          ###   ########.fr       */
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

/* node has token and next node address */
static t_token_node *make_node(char *type, char *value)
{
    t_token_node *new_node;

    new_node = (t_token_node *)malloc(sizeof(t_token_node));
    /* check null safety */
    new_node->token = make_token(type, value);
    new_node->next = 0;
    return (new_node);
}

static t_linked_list *make_list()
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

static char *is_redirection(char ch, int *index, char *str)
{
    char *value;

    if (ch == '>')
    {
        if (str[*index + 1] == '>')  // ch == '>>'
        {
            value = (char *)malloc(sizeof(char) * 3);
            value[0] = '>';
            value[1] = '>';
            value[2] = '\0';
            (*index)++;
        }
        else                        // ch == '>'
        {
            value = (char *)malloc(sizeof(char) * 2);
            value[0] = '>'
            value[1] = '\0';
        }
    }
    else
    {
        if (str[*index + 1] == '<')  // ch == '<<'
        {
            value = (char *)malloc(sizeof(char) * 3);
            value[0] = '<';
            value[1] = '<';
            value[2] = '\0';
        }
        else                        // ch == '<'
        {
            value = (char *)malloc(sizeof(char) * 2);
            value[0] = '<';
            value[1] = '\0';
        }
    }
    return (value);
}

static char *is_operator(char ch, int index, char *str)

/* lexical analysis */
t_list *tokenize(char *str)
{
    int i;
    t_list *list;
    char *cmd_line;

    i = 0;
    list = make_list();
    cmd_line = ft_strtrim(str);
    while (cmd_line[i])
    {
        
    }
}