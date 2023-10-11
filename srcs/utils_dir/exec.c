/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:03:02 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/11 14:17:59 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_word(t_tree_node *node)
{
	printf("exec %s\n", node->token->value);
}

void run_redirection_list(t_tree_node *node, t_tree_node **read_redir, t_tree_node **write_redir)
{
	t_tree_node *child;

	child = node->child_list;
	while (child)
	{
		//redirection
		if (child->token->redir_type == SINGLE_REDIR)
		{
			if (child->token->value[0] == '<')	//read_redir
				*read_redir = child;
			else	//write_redir
				*write_redir = child;
		}
		else	//DOUBLE_REDIR
		{
			printf("<< or >>\n");			
		}
		child = child->next;	
	}
}

void run_simple_command_element(t_tree_node *node)
{
	t_tree_node *child;

	child = node->child_list;
	run_word(child);
}

void run_simple_command(t_tree_node *node)
{
	t_tree_node *child;
	t_tree_node *read_redir;
	t_tree_node *write_redir;

	child = node->child_list;
	read_redir = 0;
	write_redir = 0;
	while (child)
	{
		if (child->symbol == REDIRECTION_LIST)
			run_redirection_list(child, &read_redir, &write_redir);
		child = child->next;
	}
	child = node->child_list;
	printf("-------simple_command---------\n");
	while (child)
	{
		if (child->symbol == SIMPLE_COMMAND_ELEMENT)
			run_simple_command_element(child);
		child = child->next;
	}
	if (read_redir)
		printf("[read_redir : %s]\n", read_redir->token->value);
	if (write_redir)
		printf("[write_redir : %s]\n", write_redir->token->value);
	printf("-------simple_command end---------\n");
}

// void run_subshell(t_tree_node *node)
// {
// 	t_tree_node *child;

// 	child = node->child_list;
// 	run_list(child->next); //first child is '('

// }

void run_command(t_tree_node *node, t_fd *p_fd)
{
	t_tree_node *child;
	t_tree_node *redirection_list;

	child = node->child_list;
	else if (child->symbol == SIMPLE_COMMAND)
		run_simple_command(child); // simple command에서 elements를 조합
	else //SUBSHELL
		run_list();
	// check redirection list
	// 	if (child->num_of_child > 1)	//subshell + redirection list
	// 	{
	// 		redirection_list = child->child_list->next;
	// 		while (redirection_list)
	// 		{
				
	// 		}
	// 	}
	// 	run_subshell(child);
	// }
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