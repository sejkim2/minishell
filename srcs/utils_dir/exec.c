/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:03:02 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/10 17:53:23 by sejkim2          ###   ########.fr       */
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

void run_command(t_tree_node *node)
{
	t_tree_node *child;
	t_tree_node *redirection_list;

	child = node->child_list;
	if (child->symbol == SIMPLE_COMMAND)
		run_simple_command(child);
	// else //node->child_list->symbol == SUBSHELL
	// {
	// 	// check redirection list
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

void run_pipeline(t_tree_node *node)
{
	int read_pipe[2];
	int write_pipe[2];

	t_tree_node *child;
	child = node->child_list;
	if (node->num_of_child > 1)
	{
		pipe(read_pipe);
		pipe(write_pipe);
	}
	run_command(child);
	/*	pipeline -> pipeline | command	*/
	if (node->num_of_child > 1)
		//child->next : symbol is pipe
		run_pipeline(child->next->next);
}

void run_list(t_tree_node *node)
{
	t_tree_node *child;

	child = node->child_list;
	run_pipeline(child);
}

void	run_exec(t_tree_node *root)
{
	t_tree_node *child;

	child = root->child_list;
	run_list(child);
}
