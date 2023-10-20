/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:35:29 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/20 14:56:15 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*input_heredoc(char *limit)
{
	char	*tmp_name;
	int		hd_fd;
	char	*line;

	tmp_name = generate_temp_filename("HD_Temp");
	hd_fd = open(tmp_name, O_RDWR | O_CREAT, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(limit, line, ft_strlen(line)))
		{
			free(line);
			break ;
		}
		write(hd_fd, line, ft_strlen(line));
		write(hd_fd, "\n", 1);
		free(line);
	}
	close(hd_fd);
	return (tmp_name);
}

void	get_heredoc(t_tree_node *node, int depth)
{
	t_tree_node	*child;

	if (node->symbol == REDIRECTION && \
	node->token->redir_type == DOUBLE_REDIR \
	&& node->token->value[0] == '<' && node->token->value[1] == '<')
	{
		node->token->HD_name = input_heredoc(set_redir_file_name(node));
		return ;
	}
	child = node->child_list;
	if (child)
	{
		while (child)
		{
			get_heredoc(child, depth + 1);
			child = child->next;
		}
	}
}
