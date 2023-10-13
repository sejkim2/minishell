/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:03:02 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/13 18:37:09 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_root(t_tree_node *root, char **env)
{
	t_tree_node	*child;

	child = root->child_list;
	run_list(child, env);
}

void	run_list(t_tree_node *node, char **env)
{
	t_tree_node	*child;
	int			flag;
	int			status;
	int			iput[2];

	pipe(iput);
	child = node->child_list; //symbol: PIPELINE, LIST, AND_IF, OR_IF
	run_pipeline(child, iput, env, PIPELINE); // run_pipeline의 반환으로 실행 여부를 확인.
	child = child->next;
	flag = WEXITSTATUS(status);
	while (child && ((child->symbol == AND_IF && !flag) || (child ->symbol == OR_IF && flag)))
	{
		child = child->next;
		run_list(child, env);
		child = child->next;
	}
}

void	run_pipeline(t_tree_node *node, int *iput, char **env, t_symbol	last_symbol)
{
	int			oput[2];
	t_tree_node	*child;
	pid_t		c_pro;
	t_symbol	before;

	child = node->child_list; //COMMAND, PIPE, PIPELINE
	if (child->num_of_child > 1) // 넘어갈수록 줄여줘야 할 듯?
		pipe(oput[2]);
	else if (last_symbol != PIPE)
		return (run_command_nonpipe(child, env)); //
	while (child) //next가 null로 도달할 때 까지 단, pipe는 넘김)
	{
		if (child->symbol == PIPE)
		{
			before = child->symbol;
			child = child ->next;
			return (run_pipeline(child, iput, env, before));
		}
		c_pro = fork();
		if (c_pro)
			run_command(child, iput, oput, env);
		else
		{
			iput = oput;
			child = child->next;
		}
	}
}
