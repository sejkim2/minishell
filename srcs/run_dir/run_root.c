/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:03:02 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/23 15:11:09 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_root(t_tree_node *root, char ***env, int *o_fd)
{
	t_tree_node	*child;

	child = root->child_list;
	run_list(child, env, o_fd);
}
