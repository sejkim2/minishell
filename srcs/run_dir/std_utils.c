/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:55:17 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/23 14:58:25 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_std_fd(int *o_fd)
{
	o_fd[0] = dup(0);
	o_fd[1] = dup(1);
}

void	recover_std_fd(int *o_fd)
{
	close(0);
	close(1);
	dup2(o_fd[0], 0);
	dup2(o_fd[1], 1);
}

void	unlink_tmpfile(t_tree_node *redir_list)
{
	t_tree_node	*child;

	while (redir_list)
	{
		child = redir_list->child_list;
		while (child)
		{
			if (child->symbol == REDIRECTION)
			{
				unlink(child->token->HD_name);
				free(child->token->HD_name);
				child->token->HD_name = 0;
			}
			child = child->next;
		}
		redir_list = redir_list->next;
	}
}
