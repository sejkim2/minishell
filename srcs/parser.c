/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:57:18 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/13 19:58:38 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void print_symbol(t_symbol symbol)
{
    switch (symbol)
    {
    case WORD:
        printf("WORD\n");
        break;
    case ASSIGNMENT_WORD:
        printf("ASSIGNMENT_WORD\n");
        break;
    case REDIRECTION:
        printf("REDIRECTION\n");
        break;
    case PIPE:
        printf("PIPE\n");
        break;
    case AND_IF:
        printf("AND_IF\n");
        break;
    case OR_IF:
        printf("OR_IF\n");
        break;
    case EQUAL:
        printf("EQUAL\n");
        break;
    case L_BRA:
        printf("L_BRA\n");
        break;
    case R_BRA:
        printf("R_BRA\n");
        break;
    case SIMPLE_COMMAND:
        printf("SIMPLE_COMMAND\n");
        break;
    case SIMPLE_COMMAND_ELEMENT:
        printf("SIMPLE_COMMAND_ELEMENT\n");
        break;
    case COMMAND:
        printf("COMMAND\n");
        break;
    case PIPELINE:
        printf("PIPELINE\n");
        break;
    case SUBSHELL:
        printf("SUBSHELL\n");
        break;
    case LIST:
        printf("LIST\n");
        break;
    case ROOT:
        printf("ROOT\n");
        break;
    default:
        break;
    }
}

static void traverse(t_tree_node *node, int depth)
{
    for(int i = 0; i<depth; i++)
        printf("\t\t");
    print_symbol(node->token->symbol);
    t_tree_node *child;
    while (node->)
}

static t_symbol next_symbol(t_linked_list *list)
{
    t_token_node *node;
    t_symbol symbol;

    node = pop_list(list);
    symbol = node->token->symbol;
    // free(node)
    return (symbol);
}

static void parse_error(void)
{
    printf("parse error\n");
    exit(1);
}

static int accept(t_linked_list *list, t_symbol symbol)
{
    if (list->num_of_node == 0)
        return (0);
    return (list->head->token->symbol == symbol);
}

static int expect(t_linked_list *list, t_symbol symbol)
{
    if (!accept(list, symbol))
        parse_error();
    else
        return (1);
}

static void parse_simple_command_element(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;

    if (accept(list, WORD) || accept(list, ASSIGNMENT_WORD) || accept(list, REDIRECTION))
    {
        node = make_tree_node();
        node->token->symbol = next_symbol(list);
        addchild(parent, node);
    }
    else
        parse_error();
}

static void parse_simple_command(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;

    if (accept(list, WORD) || accept(list, ASSIGNMENT_WORD) || accept(list, REDIRECTION))
    {
        node = make_tree_node();
        node->token->symbol = next_symbol(list);
        addchild(parent, node);
    }
    else
        parse_error();
}

static void parse_command(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;

    if (accept(list, WORD) || accept(list, REDIRECTION))
    {
        node = make_tree_node();
        node->token->symbol = SIMPLE_COMMAND;
        addchild(parent, node);
        parse_simple_command(list, node);
    }
    else if (accept(list, L_BRA))
    {
        node = make_tree_node();
        node->token->symbol = SUBSHELL;
        addchild(parent, node);
        parse_subshell(list, node);
    }
    else
        parse_error();
}

static void parse_pipeline(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;

    node = make_tree_node();
    node->token->symbol = COMMAND;
    addchild(parent, node);
    parse_command(list, node);
    if (accept(list, PIPE))
    {
        node = make_tree_node();
        node->token->symbol = next_symbol(list);
        addchild(parent, node);
        node = make_tree_node();
        node->token->symbol = PIPELINE;
        addchild(parent, node);
        parse_pipeline(list, node);
    }
}

static void parse_list(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;

    node = make_tree_node();
    node->token->symbol = PIPELINE;
    addchild(parent, node);
    parse_pipeline(list, node);
    if (accept(AND_IF) || accept(OR_IF))
    {
        node = make_tree_node();
        node->token->symbol = next_symbol(list);
        addchild(parent, node);
        parse_list(list, node);
    }
}

static void parse_subshell(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;

    expect(list, L_BRA);
    node = make_tree_node();
    addchild(parent, node);
    node = make_tree_node();
    node->token->symbol = LIST;
    addchild(parent, node);
    parse_list(list, node);
    expect(list, R_BRA);
    node = make_tree_node();
    node->token->symbol = next_symbol(list);
    addchild(parent, node);
}

static void parser(t_linked_list *list, t_tree_node *root)
{
    t_tree_node *node;

    node = make_tree_node();
    if (accept(list, WORD) || accept(list, ASSIGNMENT_WORD) || accept(list, REDIRECTION))
    {
        node->token->symbol = LIST;
        addchild(root, node);
        parse_list(list, node);
    }
    else if (accept(list, L_BRA))
    {
        node->token->symbol = COMMAND;
        addchild(root, node);
        parse_command(list, node);
    }
    else
        parse_error();
}