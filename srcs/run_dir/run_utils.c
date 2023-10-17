/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:07:55 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/16 18:38:00 by jaehyji          ###   ########.fr       */
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
	dup2(o_fd[0], 0);
	dup2(o_fd[1], 1);
}

int	cnt_cmd_element(t_tree_node *node)
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

char	*find_command(t_tree_node *node)
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
		cmd_info.cmd_line = (char **)malloc(sizeof(char *) * cnt_cmd_element(node) + 1);
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