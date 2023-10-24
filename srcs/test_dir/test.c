/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:46:39 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/24 13:42:49 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_symbol(t_symbol symbol)
{
    switch (symbol)
    {
    case WORD:
        printf("WORD");
        break;
    case REDIRECTION_LIST:
        printf("REDIRECTION_LIST");
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

void    tree_traverse(t_tree_node *node, int depth)
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

void	print_list(t_linked_list *list)
{
	t_token_node	*cur;

	cur = list->head;
	while (cur)
	{
		printf("[ symbol : %d value : %s]", cur->token->symbol, cur->token->value);
		if (cur->token->str_info != 0)
		{
			int i = 0;
			printf("[");
			while (cur->token->str_info[i].str_type != NUL)
			{
				printf("str : %s , type : %d ", cur->token->str_info[i].str, cur->token->str_info[i].str_type);
				i++;
			}
			printf("]");
		}
		else
			printf("[str is meta]");
		if (cur->token->redir_type == SINGLE_REDIR)
			printf("[single redir]");
		else if(cur->token->redir_type == DOUBLE_REDIR)
			printf("[double redir]");
		else if (cur->token->redir_type == NO_REDIR)
			printf("[no redir]");
		printf("\n");
		cur = cur->next;
	}
}
