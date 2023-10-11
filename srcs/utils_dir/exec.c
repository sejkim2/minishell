/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:03:02 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/11 13:47:46 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_command(t_tree_node *node, t_fd *p_fd)
{
	t_tree_node *child;
	t_tree_node *redirection_list;

	child = node->child_list;
	if (child->symbol == REDIRECTION)
		run_redirection();	//run_redirection > dup
	else if (child->symbol == SIMPLE_COMMAND)
		run_simple_command(child); // simple command에서 elements를 조합
	else //SUBSHELL
		run_list();
}

void run_pipeline(t_tree_node *node, t_fd *p_fd)
{
	t_tree_node *child;
	pid_t	c_pro;

	child = node->child_list; //COMMAND
	if (child->num_of_child > 1)
	{
		pipe(p_fd->iput[2]);
		pipe(p_fd->oput[2]);
	}
	while ()//next가 null로 도달할 때 까지 단, pipe는 넘김)
	{
		c_pro = fork();
		if (c_pro)
			run_command(child, p_fd);
		else
			child = child->next;
	}
}

void run_list(t_tree_node *node, t_fd *p_pd)
{
	t_tree_node *child;

	child = node->child_list; //symbol: pipeline
	while (1)//next가 null로 도달할 때 까지)
	{
		run_pipeline(child, p_fd);
		if (1)//and_if | or_if에 따라)
			//while 문을 더 돌릴지 말지(tree탐색) 결정 
	}
}

void	run_exec(t_tree_node *root)
{
	t_tree_node *child;
	t_fd		p_fd;

	p_fd = init_fd_struct();
	child = root->child_list;
	run_list(child, &p_fd);
}
