/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:07:55 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/20 20:19:01 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	setting_cmdinfo(t_tree_node *node, t_cmd *cmd_info)
{
	cmd_info->cmd_line = NULL;
	while (node)
	{
		if (node->symbol == SIMPLE_COMMAND_ELEMENT)
		{
			cmd_info->cmd = node->token->value;
			return ;
		}
		node = node->next;
	}
	cmd_info->cmd = NULL;
}

static int	cmd_malloc_size(t_tree_node *node)
{
	int		cnt;
	char	**table;

	cnt = 0;
	while (node)
	{
		if (node->symbol == SIMPLE_COMMAND_ELEMENT)
		{
			table = get_file_by_wild_card(node->child_list->token->str_info);
			if (!*table) // null이 어디부터인지 확인.
				cnt++;
			else
				cnt += cnt_line(table);
			free_arr(table);
		}
		node = node->next;
	}
	return (cnt);
}

void	make_cmd_line(t_tree_node *node, t_cmd *cmd_info)
{
	int		i;
	int		j;
	char	**table;

	i = 0;
	j = 0;
	while (node)
	{
		if (node->symbol == SIMPLE_COMMAND_ELEMENT)
		{
			table = get_file_by_wild_card(node->token->str_info);
			if (!*table)
				cmd_info->cmd_line[i++] = node->token->value;
			else
			{
				while (table[j])
					cmd_info->cmd_line[i++] = table[j++];
				free_arr(table);
			}
		}
		node = node->next;
	}
}

t_cmd	make_cmd_info(t_tree_node *node, char **env) //SIMPLE COMMAND ELEMENT
{
	int		cnt;
	char	*table;
	t_cmd	cmd_info;

	setting_cmdinfo(node, &cmd_info);
	cnt = cmd_malloc_size(node);
	if (cmd_info.cmd)
	{
		cmd_info.cmd_line = malloc(sizeof(char *) * (cnt + 1));
		make_cmd_line(node, &cmd_info);
		cmd_info.cmd_line[cnt] = NULL;
	}
	return (cmd_info);
}
