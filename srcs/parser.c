/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:57:18 by sejkim2           #+#    #+#             */
/*   Updated: 2023/09/11 17:49:13 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void init_tree_manager(t_tree_manager *tree)
{
    tree->root_node = 0;
    tree->num_of_node = 0;
}

static t_tree_manager *make_tree_manager(void)
{
    t_tree_manager *new_tree;

    new_tree = (t_tree_manager *)malloc(sizeof(t_tree_manager));
    init_tree_manager(new_tree);
    return (new_tree);
}

static t_tree_node *make_tree_node(void)
{
    t_tree_node *new_node;

    new_node = (t_tree_node *)malloc(sizeof(t_tree_node));
    new_node->list = (t_linked_list *)malloc(sizeof(t_linked_list));
    new_node->blanket_flag = 0;
    new_node->sub_tree = 0;
    new_node->left_child = 0;
    new_node->right_child = 0;
    return (new_node);
}

static	void	print_list(t_linked_list *list)
{
	t_token_node	*cur;

	cur = list->head;
	while (cur)
	{
		printf("[ token : %s type : %d ]", \
		cur->token->token_value, cur->token->token_type);
        if (cur == list->tail)
            break;
		cur = cur->next;
	}
}

void visited(t_tree_node *node)
{
    print_list(node->list);
    printf("\n");
    if (node->left_child != 0) {
        printf("left child: ");
        visited(node->left_child);
    }
    if (node->right_child != 0) {
        printf("right child: ");
        visited(node->right_child);
    }
    printf("\n");
}

t_tree_manager *parser(t_linked_list *list)
{
    t_token_node *cur;
    t_tree_node *child_node;
    t_tree_manager *manager;
    t_tree_node *new_root;

    cur = list->head;
    child_node = make_tree_node();
    manager = make_tree_manager();
    manager->root_node = child_node;
    manager->num_of_node++;
    new_root = 0;
    
    while (cur)
    {
        if (cur->token->token_type == AND_IF || cur->token->token_type == OR_IF)
        {
            new_root = make_tree_node();
            push_back_list(new_root->list, cur);
            
            if (manager->num_of_node == 1)
                new_root->left_child = child_node;
            else
            {
                manager->root_node->right_child = child_node;
                new_root->left_child = manager->root_node;
            }
            manager->root_node = new_root;
            manager->num_of_node++;
            child_node = make_tree_node();
        }
        else if (cur->token->token_type == LEFT_BLANKET)
        {
            while (cur)
            {
                push_back_list(child_node->list, cur);
                if (cur->token->token_type == RIGHT_BLANKET)
                    break;
                cur = cur->next;
            }
            child_node->blanket_flag = 1;
        }
        else    //simple command
            push_back_list(child_node->list, cur);
        cur = cur->next;
    }
    if (child_node->list->num_of_node > 0 && manager->num_of_node > 1)
        manager->root_node->right_child = child_node;

    visited(manager->root_node);
    return (manager);
}