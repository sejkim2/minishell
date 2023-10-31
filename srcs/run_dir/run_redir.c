/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:38:10 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/31 20:12:53 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_single_redir(t_tree_node *child, char *expand_file)
{
	int		fd;

	if (child->token->value[0] == '<')
	{
		fd = open(expand_file, O_RDONLY);
		if (fd == -1)
			return (open_error(expand_file));
		dup2(fd, 0);
	}
	else
	{
		fd = open(expand_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (open_error(expand_file));
		dup2(fd, 1);
	}
	return (0);
}

static int	expand_double_redir(char *expand_file)
{
	int		fd;

	fd = open(expand_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (open_error(expand_file));
	dup2(fd, 1);
	return (0);
}

static int	check_single_redir(t_tree_node *child, char *redir_name, \
char **file_table)
{
	int		fd;
	int		cnt;

	cnt = cnt_line(file_table);
	if (cnt > 1)
		return (wild_card_error(redir_name, cnt));
	else if (cnt == 1)
		return (expand_single_redir(child, *file_table));
	if (child->token->value[0] == '<')
	{
		fd = open(redir_name, O_RDONLY);
		if (fd == -1)
			return (open_error(redir_name));
		dup2(fd, 0);
	}
	else
	{
		fd = open(redir_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (open_error(redir_name));
		dup2(fd, 1);
	}
	return (0);
}

static int	check_double_redir(t_tree_node *child, char *redir_name, \
char **file_table)
{
	int		fd;
	int		cnt;

	cnt = cnt_line(file_table);
	if (child->token->value[0] == '>')
	{
		if (cnt > 1)
			return (wild_card_error(redir_name, cnt));
		else if (cnt == 1)
			return (expand_double_redir(*file_table));
		fd = open(redir_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (open_error(redir_name));
		dup2(fd, 1);
	}
	else
	{
		fd = open(child->token->hd_name, O_RDONLY);
		dup2(fd, 0);
	}
	return (0);
}

int	run_redirection_list(t_tree_node *node, char ***env)
{
	t_tree_node		*child;
	char			*redir_name;
	int				fd_flag;
	char			**file_table;

	child = node->child_list;
	parser_env_in_tree(child, *env);
	while (child)
	{
		file_table = get_file_by_wild_card(child->token->str_info);
		redir_name = set_redir_file_name(child);
		if (child->token->redir_type == SINGLE_REDIR)
			fd_flag = check_single_redir(child, redir_name, file_table);
		else
			fd_flag = check_double_redir(child, redir_name, file_table);
		child = child->next;
		free_arr(file_table);
		free_str(redir_name);
		if (fd_flag == -1)
			return (fd_flag);
	}
	return (0);
}
