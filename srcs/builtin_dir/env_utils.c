/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:42:37 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/26 16:21:32 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_strings(int *i, char **string, char **str)
{
	int		ldx;

	ldx = *i;
	str[0] = ft_substr(*string, 0, *i);
	if (!str[0])
		malloc_error();
	while ((*string)[ldx + 1] && (*string)[ldx + 1] != '$' \
	&& (*string)[ldx + 1] != ' ')
		ldx++;
	str[1] = ft_substr(*string, *i, (ldx + 1) - *i);
	if (!str[1])
		malloc_error();
	str[2] = ft_strdup("\0");
	if (!str[2])
		malloc_error();
	if ((*string)[ldx + 1])
	{
		free(str[2]);
		str[2] = ft_substr(*string, ldx + 1, ft_strlen(*string) - ldx);
		if (!str[2])
			malloc_error();
	}
}

void	expand_env(t_tree_node *parent, char **env)
{
	int			i;
	int			j;
	t_tree_node	*child;
	t_tree_node	*head;

	child = parent->child_list;
	while (child)
	{
		head = child;
		i = 0;
		while (child->token->str_info[i].str_type != NUL)
		{
			if (child->token->str_info[i].str_type != SINGLE_QUOTE)
				parser_env(i, child, env);
			i++;
		}
		child->token->value = apply_in_tree(child, head);
		child = child->next;
	}
}

char	**init_setting(char **envp, int *o_fd)
{
	int		cnt;
	char	**env;

	cnt = cnt_line(envp);
	env = (char **)malloc(sizeof(char *) * (cnt + 1));
	matrix_cpy(env, envp);
	store_std_fd(o_fd);
	g_exit_status = 0;
	return (env);
}

char	*get_envname(char *av)
{
	int		idx;
	char	*rstr;

	idx = 0;
	while (av[idx] && av[idx] != '=')
		idx++;
	rstr = ft_substr(av, 0, idx);
	return (rstr);
}

char	*get_envval(char *env_name, char **env)
{
	int		i;
	int		j;
	char	*compare;
	char	*rstr;

	i = 0;
	while (env[i])
	{
		j = 0;
		compare = get_envname(env[i]);
		if (!ft_strcmp(env_name, compare))
		{
			while (env[i][j] != '=')
				j++;
			rstr = ft_substr(env[i], j + 1, ft_strlen(env[i]));
			free(compare);
			return (rstr);
		}
		free(compare);
		i++;
	}
	return (NULL);
}
