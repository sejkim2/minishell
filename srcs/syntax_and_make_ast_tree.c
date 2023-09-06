/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_and_make_ast_tree.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 09:41:27 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/06 17:30:15 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_is_leaf_node(t_tree_node *node)
{
	if (node->left_child == 0 && node->right_child == 0)
		return (1);
	else
		return (0);
}

void	parser(t_linked_list *list)
{
    
}