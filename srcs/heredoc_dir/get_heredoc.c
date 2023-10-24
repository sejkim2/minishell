/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:35:29 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/24 15:55:55 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_temp_filename(char *mode)
{
	char	*str;
	char	*rstr;
	int		i;

	str = ft_strdup(mode);
	if (access(str, F_OK) == -1)
		return (str);
	while (access(str, F_OK) == 0)
	{
		i = 0;
		rstr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
		ft_memcpy(rstr, str, ft_strlen(str));
		while (i < 10)
		{
			rstr[ft_strlen(str)] = i + '0';
			rstr[ft_strlen(str) + 1] = '\0';
			if (access(rstr, F_OK) == -1)
				return (free(str), rstr);
			i++;
		}
		rstr[ft_strlen(str)] = '_';
		free(str);
		str = rstr;
	}
	return (str);
}

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
		if (!line || !ft_strcmp(limit, line))
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
