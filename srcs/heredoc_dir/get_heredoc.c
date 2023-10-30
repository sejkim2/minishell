/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:35:29 by sejkim2           #+#    #+#             */
/*   Updated: 2023/10/30 20:49:15 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(char *tmp_name)
{
	int		hd_fd;

	hd_fd = open(tmp_name, O_RDWR | O_CREAT, 0644);
	if (hd_fd == -1)
		system_call_error();
	return (hd_fd);
}

static	void	run_readline(char *limit, int hd_fd, char **env)
{
	char	*line;
	char	*tmp;

	set_heredoc_signal();
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(limit, line))
		{
			free(line);
			exit(0);
		}
		tmp = parser_env(line, environ);
		write(hd_fd, tmp, ft_strlen(tmp));
		write(hd_fd, "\n", 1);
		free(tmp);
	}
}

static	char	*input_heredoc(char *limit, char **env)
{
	char	*tmp_name;
	int		hd_fd;
	pid_t	child;
	int		status;

	tmp_name = generate_temp_filename("/tmp/HD_Temp");
	hd_fd = open_file(tmp_name);
	child = fork();
	if (child == 0)
		run_readline(limit, hd_fd, env);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(child, &status, 0);
		g_exit_status = WEXITSTATUS(status);
		if (g_exit_status == 1)
		{
			unlink(tmp_name);
			free(tmp_name);
			return (0);
		}
	}
	close(hd_fd);
	return (tmp_name);
}

static	int	check_is_heredoc(t_token *token)
{
	if (token->redir_type == DOUBLE_REDIR \
	&& token->value[0] == '<' && token->value[1] == '<')
		return (1);
	else
		return (0);
}

int	get_heredoc(t_tree_node *node, char **env)
{
	char	*file_name;

	if (check_is_heredoc(node->token) == 1)
	{
		file_name = set_redir_file_name(node);
		node->token->hd_name = input_heredoc(file_name, env);
		free(file_name);
		if (node->token->hd_name == 0)
			return (-1);
	}
	return (1);
}
