/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:38:10 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/20 14:40:31 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_redirection_list(t_tree_node *node)
{
	t_tree_node	*child;
	char		*redir_name;

	child = node->child_list;
	while (child)
	{
		redir_name = set_redir_file_name(child);
		// wild_card_in_redir(redir_name, child);
		if (child->token->redir_type == SINGLE_REDIR)
			check_single_redir(child, redir_name);
		else	//DOUBLE_REDIR
			check_double_redir(child, redir_name);
		child = child->next;
	}
}

char	*set_redir_file_name(t_tree_node *node)
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

void	check_single_redir(t_tree_node *child, char *redir_name)
{
	int		fd;

	if (child->token->value[0] == '<')
	{
		fd = open(redir_name, O_RDONLY);
		if (fd == -1)
		{
			ft_stderror_print(redir_name, NULL, strerror(errno));
			exit_status = 1;
		}
		dup2(fd, 0);
	}
	else
	{
		fd = open(redir_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			ft_stderror_print(redir_name, NULL, strerror(errno));
			exit_status = 1;
		}
		dup2(fd, 1);
	}
}

void	check_double_redir(t_tree_node *child, char *redir_name)
{
	int		fd;

	if (child->token->value[0] == '<')
	{
		fd = here_document();
		if (fd == -1)
		{
			ft_stderror_print(redir_name, NULL, strerror(errno));
			exit_status = 1;
		}
		dup2(fd, 0);
	}
	else
	{
		fd = open(redir_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_stderror_print(redir_name, NULL, strerror(errno));
			exit_status = 1;
		}
		dup2(fd, 1);
	}
}
