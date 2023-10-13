/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:07:55 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/13 18:17:44 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_cmd	make_cmd_info(t_tree_node *node, char **env)
{
	char	*tmp;
	int		idx;
	t_cmd	cmd_info;

	idx = 0;
	cmd_info.cmd = node->token->value;
	cmd_info.cmd_line = (char **)malloc(sizeof(char *) * cnt_cmd_element(node) + 1);
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
	return (cmd_info);
}