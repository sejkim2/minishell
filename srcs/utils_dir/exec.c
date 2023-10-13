/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:03:02 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/13 12:33:20 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void run_word(t_tree_node *node)
{
	printf("exec %s\n", node->token->value);
}

static void print_redir(t_tree_node *read_redir, t_tree_node *write_redir)
{
	if (read_redir)
		printf("[read_redir :%s]\n", read_redir->token->file_name);
	else
		printf("[no read redir]\n");
	if (write_redir)
		printf("[write_redir :%s]\n", write_redir->token->file_name);
	else
		printf("[no write redir]\n");
}

static char *set_redir_file_name(t_tree_node *node)
{
	char *file_name;
	char *remove_str;
	int i;

	i = 0;
	file_name = ft_strdup("");
	while (node->token->str_info[i].str_type != NUL)
	{
		remove_str = file_name;
		file_name = ft_strjoin(file_name, node->token->str_info[i].str);
		free(remove_str);
		i++;
	}
	node->token->file_name = file_name;
	return (file_name);
}

void run_redirection_list(t_tree_node *node, t_tree_node **read_redir, t_tree_node **write_redir)
{
	t_tree_node *child;

	child = node->child_list;
	while (child)
	{
		//redirection
		set_redir_file_name(child);
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
	while (child)
	{
		if (child->symbol == SIMPLE_COMMAND_ELEMENT)
			run_simple_command_element(child);
		child = child->next;
	}
	print_redir(read_redir, write_redir);
}

void run_subshell(t_tree_node *node)
{
	t_tree_node *child;

	child = node->child_list;
	run_list(child->next); //first child is '('
}


void run_command(t_tree_node *node, t_fd *p_fd)
{
	t_tree_node *child;
	t_tree_node *redirection_list;
	t_tree_node *read_redir;
	t_tree_node *write_redir;

	child = node->child_list;
	read_redir = 0;
	write_redir = 0;
	if (child->symbol == SIMPLE_COMMAND)
		run_simple_command(child);
	else //node->child_list->symbol == SUBSHELL
	{
		// check redirection list
		if (node->num_of_child > 1)	//subshell + redirection list
		{
			redirection_list = child->next;
			run_redirection_list(redirection_list, &read_redir, &write_redir);
		}
		printf("------------after subshell------------------\n");
		run_subshell(child);
		print_redir(read_redir, write_redir);
		printf("------------before subshell------------------\n");
	}
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
	printf("------------after pipe line------------------\n");
	run_command(child);
	printf("------------before pipe line-----------------\n");
	/*	pipeline -> pipeline | command	*/
	if (node->num_of_child > 1)
		//child->next : symbol is pipe
		run_pipeline(child->next->next);
}

void run_list(t_tree_node *node, t_fd *p_pd)
{
	t_tree_node *child;

	child = node->child_list;
	run_pipeline(child);

}

void	run_exec(t_tree_node *root)
{
	t_tree_node *child;
	t_fd		p_fd;

	p_fd = init_fd_struct();
	child = root->child_list;
	run_list(child, &p_fd);
}
