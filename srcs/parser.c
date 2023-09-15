/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:57:18 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/15 21:19:11 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_tree_node *make_tree_node(void)
{
    t_tree_node *node;

    node = (t_tree_node *)malloc(sizeof(t_tree_node));
    // node->symbol = WORD;
    node->num_of_child = 0;
    node->next = 0;
    node->child_list = 0;
    return (node);
}

static void addchild(t_tree_node *parent, t_tree_node *child)
{
    t_tree_node *cur;

    cur = parent->child_list;
    if (parent->num_of_child == 0)
        parent->child_list = child;
    else
    {
        while (cur->next)
            cur = cur->next;
        cur->next = child;
    }
    (parent->num_of_child)++;
}

static void print_symbol(t_symbol symbol)
{
    switch (symbol)
    {
    case WORD:
        printf("WORD");
        break;
    case REDIRECTION_LIST:
        printf("REDIRECTION_LIST");
        break;
    case ASSIGNMENT_WORD:
        printf("ASSIGNMENT_WORD");
        break;
    case REDIRECTION:
        printf("REDIRECTION");
        break;
    case PIPE:
        printf("PIPE");
        break;
    case AND_IF:
        printf("AND_IF");
        break;
    case OR_IF:
        printf("OR_IF");
        break;
    case EQUAL:
        printf("EQUAL");
        break;
    case L_BRA:
        printf("L_BRA");
        break;
    case R_BRA:
        printf("R_BRA");
        break;
    case SIMPLE_COMMAND:
        printf("SIMPLE_COMMAND");
        break;
    case SIMPLE_COMMAND_ELEMENT:
        printf("SIMPLE_COMMAND_ELEMENT");
        break;
    case COMMAND:
        printf("COMMAND");
        break;
    case PIPELINE:
        printf("PIPELINE");
        break;
    case SUBSHELL:
        printf("SUBSHELL");
        break;
    case LIST:
        printf("LIST");
        break;
    case ROOT:
        printf("ROOT");
        break;
    default:
        break;
    }
}

static void tree_traverse(t_tree_node *node, int depth)
{
    for(int i = 0; i<depth; i++)
        printf("\t");
    printf("symbol : ");
    print_symbol(node->symbol);
    if (node->token != 0)
        printf(" value : %s\n", node->token->value);
    else
        printf(" value : root\n");

    t_tree_node *child;
    child = node->child_list;
    if (child)
    {
        while (child)
        {
            tree_traverse(child, depth + 1);
            child = child->next;
        }
    }
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
    {
        parse_error();
        return (0);
    }
    else
        return (1);
}

void parse_simple_command_element(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;

    if (accept(list, WORD) || accept(list, ASSIGNMENT_WORD) || accept(list, REDIRECTION))
    {
        node = make_tree_node();
        node->token = list->head->token;
        node->symbol = next_symbol(list);
        addchild(parent, node);
    }
    else
        parse_error();
}

void parse_redirection_list(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;

    while (1)
    {
        if (accept(list, REDIRECTION))
        {
            node = make_tree_node();
            node->token = list->head->token;
            node->symbol = next_symbol(list);
            addchild(parent, node);
        }
        else
            break;
    }
}

void parse_simple_command(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;

    while (1)
    {
        if (accept(list, WORD) || accept(list, ASSIGNMENT_WORD) || accept(list, REDIRECTION))
        {
            if (accept(list, REDIRECTION))
            {
                node = make_tree_node();
                node->symbol = REDIRECTION_LIST;
                node->token = list->head->token;
                addchild(parent, node);
                parse_redirection_list(list, node);
            }
            else
            {
                node = make_tree_node();
                node->symbol = SIMPLE_COMMAND_ELEMENT;
                node->token = list->head->token;
                addchild(parent, node);
                parse_simple_command_element(list, node);
            }
        }
        else
            break;
    }
}

void parse_command(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;

    node = make_tree_node();
    if (accept(list, WORD) || accept(list, ASSIGNMENT_WORD) || accept(list, REDIRECTION))
    {
        node->symbol = SIMPLE_COMMAND;
        node->token = list->head->token;
        addchild(parent, node);
        parse_simple_command(list, node);
    }
    else if (accept(list, L_BRA))
    {
        node->symbol = SUBSHELL;
        node->token = list->head->token;
        addchild(parent, node);
        parse_subshell(list, node);
        if (accept(list, REDIRECTION))
        {
            node = make_tree_node();
            node->symbol = REDIRECTION_LIST;
            node->token = list->head->token;
            addchild(parent, node);
            parse_redirection_list(list, node);
        }
    }
    else
        parse_error();
}

void parse_pipeline(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;
    t_symbol symbol;

    node = make_tree_node();
    node->symbol = COMMAND;
    node->token = list->head->token;
    addchild(parent, node);
    parse_command(list, node);
    if (accept(list, PIPE))
    {
        node = make_tree_node();
        node->token = list->head->token;
        node->symbol = next_symbol(list);
        addchild(parent, node);
        symbol = list->head->token->symbol;
        if (symbol == PIPE || symbol == AND_IF || symbol == OR_IF || symbol == R_BRA)
        {
            printf("parse error\n");
            exit(1);
        }
        node = make_tree_node();
        node->symbol = PIPELINE;
        node->token = list->head->token;
        addchild(parent, node);
        parse_pipeline(list, node);
    }
}

void parse_list(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;
    t_symbol symbol;

    node = make_tree_node();
    node->symbol = PIPELINE;
    node->token = list->head->token;
    addchild(parent, node);
    parse_pipeline(list, node);
    if (accept(list, AND_IF) || accept(list, OR_IF))
    {
        node = make_tree_node();
        node->token = list->head->token;
        node->symbol = next_symbol(list);
        addchild(parent, node);
        symbol = list->head->token->symbol;
        if (symbol == PIPE || symbol == AND_IF || symbol == OR_IF || symbol == R_BRA)
        {
            printf("parse error\n");
            exit(1);
        }
        node = make_tree_node();
        node->symbol = LIST;
        node->token = list->head->token;
        addchild(parent, node);
        parse_list(list, node);
    }
}

void parse_subshell(t_linked_list *list, t_tree_node *parent)
{
    t_tree_node *node;

    expect(list, L_BRA);
    node = make_tree_node();
    node->token = list->head->token;
    node->symbol = next_symbol(list);
    addchild(parent, node);
    node = make_tree_node();
    node->symbol = LIST;
    addchild(parent, node);
    parse_list(list, node);
    expect(list, R_BRA);
    node = make_tree_node();
    node->token = list->head->token;
    node->symbol = next_symbol(list);
    addchild(parent, node);
}

void parser(t_linked_list *list)
{
    t_tree_node *root;
    t_tree_node *node;

    root = make_tree_node();
    root->symbol = ROOT;
    root->token = 0;
    node = make_tree_node();

    if (accept(list, WORD) || accept(list, ASSIGNMENT_WORD) || accept(list, REDIRECTION) || accept(list, L_BRA))
    {
        node->symbol = LIST;
        node->token = list->head->token;
        addchild(root, node);
        parse_list(list, node);
    }
    else
        parse_error();

    tree_traverse(root, 0);
}
