/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:03:02 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/17 20:10:08 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_root(t_tree_node *root, char ***env)
{
	t_tree_node	*child;
	int			iput[2];

	pipe(iput);
	close(iput[1]);
	child = root->child_list;
	run_list(child, iput, env);
}

void	run_list(t_tree_node *node, int *iput, char ***env)
{
	t_tree_node	*child;
	int			status;

	child = node->child_list; //symbol: PIPELINE, LIST, AND_IF, OR_IF
	run_pipeline(child, iput, env, PIPELINE);
	child = child->next;
	while (child && ((child->symbol == AND_IF && !exit_status) || (child ->symbol == OR_IF && exit_status)))
	{
		child = child->next;
		run_list(child, iput, env);
		child = child->next;
	}
}

void	run_pipeline(t_tree_node *node, int *iput, char ***env, t_symbol last_symbol)
{
	int			oput[2];
	t_tree_node	*child;
	pid_t		c_pro;

	if (node->num_of_child > 1) //pipeline의 하위 개념수 (1이상이면 반드시 파이프가 존재한다.)
	{
		pipe(oput);
		close(oput[0]);
	}
	child = node->child_list; //COMMAND, PIPE, PIPELINE
	if (node->num_of_child == 1 && last_symbol != PIPE)
		return (run_command_nonpipe(child, env));
	else if (node->num_of_child == 1 && last_symbol == PIPE)
		return (run_command_lastpipe(child, iput, env));
	while (child) //COMMAND, PIPE, PIPELINE. 단, PIPE는 넘김)
	{
		if (child->symbol == PIPE)
			return (run_pipeline(child->next, iput, env, child->symbol));
		c_pro = fork();
		if (c_pro == 0)
		{
			run_command(child, iput, oput, env);
			exit(exit_status);
		}
		else
		{
			iput = oput;
			child = child->next;
		}
	}
}
