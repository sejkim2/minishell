/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:46:28 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/30 20:34:23 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_status_env(int *i, char *line)
{
	t_env_str_2	s;
	char		*tmp[2];

	s.fstr = ft_substr(line, 0, *i - 1);
	check_malloc_fail(s.fstr);
	s.env_str = ft_itoa((int)g_exit_status);
	check_malloc_fail(s.env_str);
	s.bstr = ft_substr(line, *i + 1, ft_strlen(line) - (*i + 1));
	check_malloc_fail(s.bstr);
	tmp[0] = ft_strjoin(s.fstr, s.env_str);
	*i = ft_strlen(s.fstr) + ft_strlen(s.env_str);
	check_malloc_fail(tmp[0]);
	tmp[1] = ft_strjoin(tmp[0], s.bstr);
	check_malloc_fail(tmp[1]);
	free_4str(s.fstr, s.env_str, s.bstr, tmp[0]);
	free(line);
	return (tmp[1]);
}

char	*expand_env(int *i, int len, char *line, char **env)
{
	t_env_str_2	s;
	char		*tmp[2];

	s.fstr = ft_substr(line, 0, *i - 1);
	check_malloc_fail(s.fstr);
	tmp[0] = ft_substr(line, *i, len - *i);
	check_malloc_fail(tmp[0]);
	s.env_str = get_envval(tmp[0], env);
	if (!s.env_str)
	{
		s.env_str = ft_strdup("\0");
		check_malloc_fail(s.env_str);
	}
	s.bstr = ft_substr(line, len, ft_strlen(line) - len);
	check_malloc_fail(s.bstr);
	tmp[0] = ft_strjoin(s.fstr, s.env_str);
	*i = ft_strlen(s.fstr) + ft_strlen(s.env_str);
	check_malloc_fail(tmp[0]);
	tmp[1] = ft_strjoin(tmp[0], s.bstr);
	check_malloc_fail(tmp[1]);
	free_4str(s.fstr, s.env_str, s.bstr, tmp[0]);
	free_2str(tmp[0], line);
	return (tmp[1]);
}

char	*check_env_case(int *i, char *line, char **env)
{
	int		envname_ldx;

	if (line[*i] == '?')
		return (exit_status_env(i, line));
	else
	{
		write(2, "here\n", 5);
		envname_ldx = get_envname_idx(i, line);
		if (envname_ldx != 0)
			return (expand_env(i, envname_ldx, line, env));
		else
			return (line);
	}
}

char	*parser_env(char *line, char **env)
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
			line = check_env_case(&i, line, env);
	}
	return (line);
}

int	get_envname_idx(int *i, char *line)
{
	int		idx;

	idx = *i;
	if (line[idx] == '_' || ft_isalpha(line[idx]))
		idx++;
	else
		return (0);
	while (line[idx] && line[idx] != '$' \
	&& line[idx] != '/' && line[idx] != ' ' \
	&& line[idx] != '\'' && line[idx] != '"')
	{
		if (line[idx] == '_' || ft_isalpha(line[idx]) || ft_isdigit(line[idx]))
			idx++;
		else
			return (0);
	}
	return (idx);
}
