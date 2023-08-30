/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 13:48:24 by sejkim2           #+#    #+#             */
/*   Updated: 2023/08/30 13:49:53 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void init_token(t_token *token, char *type, char *value)
// {
//     token->type = ft_strdup(type);
//     token->value = ft_strdup(value);
// }

// static t_token *make_token(char *type, char *value)
// {
//     t_token *new_token;

//     new_token = (t_token *)malloc(sizeof(t_token));
//     /* check null safety */
//     init_token(new_token, type, value);
//     return (new_token);
// }

// static t_token_node *make_node(char *cmd_line, int start, int end, t_type check_type)
// {
//     char *str;
//     t_token_node *new_node;

//     new_node = (t_token_node *)malloc(sizeof(t_token_node));
//     str = (char *)malloc(sizeof(char) * (end - start))
//     /* check null safety */
//     new_node->token = make_token(type, value);
//     new_node->next = 0;
//     return (new_node);
// }

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

// static int check_is_heredoc_or_append_or_andif_or_orif(char *cmd_line, int index, t_type *check_type)
// {
//     char ch;

//     ch = cmd_line[index];
//     if (ch == cmd_line[index + 1])
//     {
//         if (ch == '&')
//             *check_type = AND_IF;
//         else if (ch == '|')
//             *check_type = OR_IF;
//         else if (ch == '<')
//             *check_type = IN_REDIRECTION;
//         else if (ch == '>')
//             *check_type = OUT_REDIRECTION;
//         else
//             return (0);
//         return (1);
//     }
//     else
//         return (0);
// }

static int check_is_meta_character(char *cmd_line, int index)
{
    char ch;

    ch = cmd_line[index];
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

static int check_is_white_space(char *cmd_line, int index)
{
    char ch;

    ch = cmd_line[index];
    if (ch == ' ' || ch == '\t' || ch == '\n')
        return (1);
    else
        return (0);
}

static int check_is_seperator(char ch, t_type *check_type)
{
    if (check_is_meta_character(ch, check_type) \
        || check_is_quote(ch, check_type) \
        || check_is_white_space(ch, check_type))
        return (1);
    else
        return (0);
}

/* lexical analysis */
t_list *lexer(char *cmd_line)
{
    int i;
    int start;
    t_type token_type;
    t_linked_list *list;

    i = 0;
    start = 0;
    token_type = WORD;
    list = make_list(void);
    
    while (cmd_line[i])
    {
        while (check_is_white_space(cmd_line, i))
            i++;
        if (cmd_line[i] == '\0')
            break;
        start = i;
        if (check_is_meta_character(cmd_line, i))
        {
            token_type = set_token_type(cmd_line, i);
            push_back_list(&list, make_node(cmd_line, start, i, token_type));
            if (token_type == AND_IF || token_type == OR_IF || token_type == HEREDOC || token_type == APPEND)
                i = i + 2;
            else
                i = i + 1;
        }
        else
        {
            while (!check_is_seperator(cmd_line, i))
                i++;
            token_type = WORD;
            push_back_list(&list, make_node(cmd_line, start, i, token_type));
        }
    }
}