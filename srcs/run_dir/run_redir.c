/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:38:10 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/20 14:41:43 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*set_redir_file_name(t_tree_node *node)
{
	char	*file_name;
	char	*remove_str;
	int		i;

	i = 0;
	file_name = ft_strdup("");
	while (node->token->str_info[i].str_type != NUL)
	{
		remove_str = file_name;
		file_name = ft_strjoin(file_name, node->token->str_info[i].str);
		free(remove_str);
		i++;
	}
	return (file_name);
}

static int	*check_single_redir(t_tree_node *child, char *redir_name)
{
	int		fd;

	if (child->token->value[0] == '<')
	{
		fd = open(redir_name, O_RDONLY);
		if (fd == -1)
		{
			ft_stderror_print(redir_name, NULL, strerror(errno));
			return (-1);
		}
		dup2(fd, 0);
	}
	else
	{
		fd = open(redir_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_stderror_print(redir_name, NULL, strerror(errno));
			return (-1);
		}
		dup2(fd, 1);
	}
	return (fd);
}

static int	*check_double_redir(t_tree_node *child, char *redir_name)
{
	int		fd;

	if (child->token->value[0] == '>')
	{
		fd = open(redir_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_stderror_print(redir_name, NULL, strerror(errno));
			return (-1);
		}
		dup2(fd, 1);
	}
	else
	{
		fd = open(child->token->hd_name, O_RDONLY);
		if (fd == -1)
		{
			ft_stderror_print(redir_name, NULL, strerror(errno));
			return (-1);
		}
		dup2(fd, 0);
	}
	return (fd);
}

int	run_redirection_list(t_tree_node *node)
{
	t_tree_node		*child;
	char			*redir_name;
	int				fd_flag;

	child = node->child_list;
	while (child)
	{
		redir_name = set_redir_file_name(child);
		if (child->token->redir_type == SINGLE_REDIR)
			fd_flag = check_single_redir(child, redir_name);
		else
			fd_flag = check_double_redir(child, redir_name);
		child = child->next;
		free(redir_name);
		if (fd_flag == -1)
			return (fd_flag);
	}
	return (0);
}
