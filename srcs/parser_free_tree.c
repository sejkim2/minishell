/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:22:41 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/20 16:49:21 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *free_tree_node(t_tree_node *node)
{
    node->next = 0;
    node->child_list = 0;
    // if (node->token != 0)
    //     free_token(node->token);
    free(node);
    return (0);
}

char *free_tree(t_tree_node *parent)
{
    t_tree_node *child;
    t_tree_node *remove_node;

    child = parent->child_list;
    if (child)
    {
        while (child)
        {
            remove_node = child;
            child = child->next;
            if (remove_node->child_list == 0)
                free_tree_node(remove_node);
            else
                free_tree(remove_node);
        }
    }
    free_tree_node(parent);
    return (0);
}