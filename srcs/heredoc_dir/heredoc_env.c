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

#include "minishell.h"

char	*heredoc_expand_env(char *line, char **env)
{
	int		i;
	char	*rstr;

	i = 0;
	rstr = line;
	while (rstr[i])
	{
		if (dollar_string(rstr))
			break ;
		if (rstr[i] != '$')
			i++;
		else
			heredoc_make_env(&i, &rstr, env);
	}
	return (rstr);
}

void	heredoc_make_env(int *idx, char **string, char **env)
{
	t_env_str	e_str;
	char		*env_val;
	char		*tmp;

	heredoc_parser_strings(idx, *string, &e_str);
	if ((*string)[*idx + 1] && (*string)[*idx + 1] == '?')
	{
		e_str.exp_str = ft_itoa((int)g_exit_status);
		free(e_str.bstr);
		e_str.bstr = ft_strdup(*string + *idx + 2);
	}
	else
	{
		env_val = get_envval(e_str.env_str + 1, env);
		if (env_val)
			e_str.exp_str = env_val;
		else
			e_str.exp_str = ft_strdup("");
	}
	tmp = ft_strjoin(e_str.fstr, e_str.exp_str);
	*idx += ft_strlen(e_str.exp_str);
	free_4str(e_str.fstr, e_str.env_str, e_str.exp_str, *string);
	*string = ft_strjoin(tmp, e_str.bstr);
	free_2str(tmp, e_str.bstr);
}

void	heredoc_parser_strings(int *i, char *string, t_env_str *e_str)
{
	int		ldx;

	ldx = *i;
	e_str->fstr = ft_substr(string, 0, *i);
	if (!e_str->fstr)
		malloc_error();
	while (string[ldx + 1] && string[ldx + 1] != '$' \
	&& (string[ldx + 1] != ' ') && (string[ldx + 1] != '/') \
	&& (string[ldx + 1] != '\'') && (string[ldx + 1] != '\"'))
		ldx++;
	e_str->env_str = ft_substr(string, *i, (ldx + 1) - *i);
	if (!e_str->env_str)
		malloc_error();
	e_str->bstr = ft_strdup("\0");
	if (!e_str->bstr)
		malloc_error();
	if (string[ldx + 1])
	{
		free(e_str->bstr);
		e_str->bstr = ft_substr(string, ldx + 1, ft_strlen(string) - ldx);
		if (!e_str->bstr)
			malloc_error();
	}
}