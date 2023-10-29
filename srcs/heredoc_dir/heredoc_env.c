/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:46:28 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/28 16:52:02 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	환경변수 조건에서 $$처럼 다수의 $에 대해 해석의 방향성이 존재하지 않으므로

	1. $$.... 처럼 다수의 $를 1개로 볼 것인가.
	2. $$.... 처럼 다수의 $가 입력되어도 마지막 $만 해석할 것인가.
*/

#include "minishell.h"

static char	*heredoc_exit_status_env(int *i, char *line)
{
	t_env_str_2	string;
	char		*tmp1;
	char		*tmp2;

	string.fstr = ft_substr(line, 0, *i - 1);
	if (!string.fstr)
		malloc_error();
	string.env_str = ft_itoa((int)g_exit_status);
	if (!string.env_str)
		malloc_error();
	string.bstr = ft_substr(line, *i + 1, ft_strlen(line) - (*i + 1))
	if (!string.bstr)
		malloc_error();
	tmp1 = ft_strjoin(string.fstr, string.env_str);
	free_2str(string.fstr, string.env_str);
	if (!tmp1)
		malloc_error();
	tmp2 = ft_strjoin(tmp1, string.bstr);
	free_2str(tmp1, string.bstr);
	if (!tmp2)
		malloc_error();
	free(line);
	*i = *i + 1;
	return (tmp2);
}

int		heredoc_check_key_rule(int *i, char *line)
{
	int		idx;

	idx = *i
	if (line[idx] == '_' || ft_isalpha(line[idx]))
		idx++;
	else
		return (0);
	while (line[idx] && line[idx] != '$')
	{
		if (line[idx] == '_' || ft_isalpha(line[idx]) || ft_isdigit(line[idx]))
			idx++;
		else
			return (0);
	}
	return (ldx);
}

static char	*heredoc_expand_env(int *i, int len, char *line, char **env)
{
	t_env_str_2	string;
	char		*tmp1;
	char		*tmp2;

	string.fstr = ft_substr(line, 0, *i - 1);
	if (!string.fstr)
		malloc_error();
	tmp1 = ft_substr(line, *i, len);
	string.env_str = get_envval(tmp1);
	free(tmp1);
	if (!string.env_str)
		string.env_str = ft_strdup("\0");
	if (!string.env_str)
		malloc_error();
	string.bstr = ft_substr(line, *i + len, ft_strlen(line) - (*i + len))
	if (!string.bstr)
		malloc_error();
	tmp1 = ft_strjoin(string.fstr, string.env_str);
	free_2str(string.fstr, string.env_str);
	if (!tmp1)
		malloc_error();
	tmp2 = ft_strjoin(tmp1, string.bstr);
	free_2str(tmp1, string.bstr);
	if (!tmp2)
		malloc_error();
	free(line);
	*i = *i + len;
	return (tmp2);
}

char	*heredoc_make_env(int *i, char *line, char **env)
{
	int		envname_len;

	if (line[*i] == '?')
		return (heredoc_exit_status_env(i, line));
	else
	{
		envname_len = heredoc_check_key_rule(i, line);
		if (envname_len != 0)
			return (heredoc_expand_env(i, envname_len, line, env));
		else
			return (line);
	}
}

char	*heredoc_check_env(char *line, char **env)
{
	int		i;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != '$')
			i++;
		while (line[i] && line[i] == '$')
			i++;
		if (!line[i])
			return (line);
		else
			line = heredoc_make_env(&i, line, env);
	}
	return (line);
}
