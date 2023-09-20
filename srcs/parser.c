/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:57:18 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/20 13:42:26 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_symbol next_symbol(t_linked_list *list)
{
    t_token_node *node;
    t_symbol symbol;

    node = pop_list(list);
    symbol = node->token->symbol;
    return (symbol);
}

int accept(t_linked_list *list, t_symbol symbol)
{
    if (list->num_of_node == 0)
        return (0);
    return (list->head->token->symbol == symbol);
}

int expect(t_linked_list *list, t_symbol symbol)
{
    if (!accept(list, symbol))
    {
        parse_error();
        return (0);
    }
    else
        return (1);
}

void parser(t_linked_list *list)
{
    t_tree_node *root;
    t_tree_node *node;

    root = make_tree_node(list, ROOT);
    root->token = 0;
    if (accept(list, WORD) || accept(list, ASSIGNMENT_WORD) || accept(list, REDIRECTION) || accept(list, L_BRA))
    {
        node = make_tree_node(list, LIST);
        addchild(root, node);
        parse_list(list, node);
    }
    else
        parse_error();

    tree_traverse(root, 0);
}
