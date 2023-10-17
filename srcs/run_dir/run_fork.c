/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:44:36 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/17 16:38:33 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_command_nonpipe(t_tree_node *node, char ***env)
{
	int			status;
	t_tree_node	*child;
	t_tree_node	*redirection_list;
	pid_t		sub_pro;

	child = node->child_list;
	if (child->symbol == SIMPLE_COMMAND)
		run_simple_command_nonpipe(child, env); // simple command에서 elements를 조합
	else
	{
		sub_pro = fork();
		if (sub_pro == 0)
		{
			if (child->next)
				run_redirection_list(child->next);
			run_list(child->child_list->next, env);
			exit(exit_status);
		}
		else
		{
			wait(&status);
			exit_status = WEXITSTATUS(status);
		}
	}
}

void	run_command(t_tree_node *node, int *iput, int *oput, char ***env)
{
	t_tree_node	*child;
	t_tree_node	*redirection_list;
	pid_t		sub_pro;

	child = node->child_list;
	if (child->symbol == SIMPLE_COMMAND)
		run_simple_command(child, iput, oput, env); // simple command에서 elements를 조합
	else //subshell
	{
		sub_pro = fork();
		if (sub_pro == 0)
			run_list(child->child_list->next, env);
	}
}
