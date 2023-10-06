/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:03:02 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/06 20:15:50 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void run_simple_command()
// {

// }

// static void run_pipeline()
// {

// }

// static void run_list(t_tree_node *parent)
// {

// }

static void run_cur_node(t_tree_node *node)
{
	print_symbol(node->symbol);
	printf("\n");
}

void	run_exec(t_tree_node *root)
{
	t_tree_node *parent;
	t_tree_node *child;

	parent = root->child_list;
	while (parent)
	{
		if (parent->num_of_child > 1)	//child list를 가지고 있을 때
		{
			run_cur_node(parent);
			parent = parent->child_list;
			while (1)
			{
				run_cur_node(parent);
				if (parent->next)
					parent = parent->next;
				else
					break;
			}
		}
		else
		{
			run_cur_node(parent);
			parent = parent->child_list;
		}
	}
}
