/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:07:55 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/20 15:05:30 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_std_fd(int *o_fd)
{
	o_fd[0] = dup(0);
	o_fd[1] = dup(1);
}

void	recover_std_fd(int *o_fd, t_tree_node *redir_list)
{
	t_tree_node	*child;

	close(0);
	close(1);
	dup2(o_fd[0], 0);
	dup2(o_fd[1], 1);
	while (redir_list)
	{
		child = redir_list->child_list;
		while (child)
		{
			if (child->symbol == REDIRECTION)
				unlink(child->token->HD_name);
			child = child->next;
		}
		redir_list = redir_list->next;
	}
}

static int	cnt_argv(t_tree_node *node)
{
	int		cnt;

	cnt = 0;
	while (node)
	{
		if (node->symbol == SIMPLE_COMMAND_ELEMENT)
			cnt++;
		node = node->next;
	}
	return (cnt);
}

static char	*find_command(t_tree_node *node)
{
	while (node)
	{
		if (node->symbol == SIMPLE_COMMAND_ELEMENT)
			return (node->token->value);
		node = node->next;
	}
	return (NULL);
}

t_cmd	make_cmd_info(t_tree_node *node, char **env)
{
	char	*tmp;
	int		idx;
	t_cmd	cmd_info;

	idx = 0;
	cmd_info.cmd = find_command(node);
	cmd_info.cmd_line = NULL;
	if (cmd_info.cmd)
	{
		cmd_info.cmd_line = malloc(sizeof(char *) * cnt_argv(node) + 1);
		if (!cmd_info.cmd_line)
			malloc_error();
		while (node)
		{
			if (node->symbol == SIMPLE_COMMAND_ELEMENT)
			{
				cmd_info.cmd_line[idx] = node->token->value;
				idx++;
			}
			node = node->next;
		}
		cmd_info.cmd_line[idx] = NULL;
	}
	return (cmd_info);
}
