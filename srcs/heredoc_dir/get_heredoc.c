/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:35:29 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/20 15:49:14 by sejkim2          ###   ########.fr       */
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
		if (!line || !strcmp(limit, line))
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

void	get_heredoc(t_tree_node *node)
{
	if (node->token->redir_type == DOUBLE_REDIR \
	&& node->token->value[0] == '<' && node->token->value[1] == '<')
		node->token->HD_name = input_heredoc(set_redir_file_name(node));
}
