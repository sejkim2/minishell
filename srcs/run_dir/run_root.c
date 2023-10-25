/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:03:02 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/25 16:39:10 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_root(t_tree_node *root, char ***env)
{
	t_tree_node	*child;

	root->fd[0] = dup(0);
	root->fd[1] = dup(1);
	child = root->child_list;
	run_list(child, env, root);
	close(root->fd[0]);
	close(root->fd[1]);
}
