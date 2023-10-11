/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 08:25:18 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/10 09:34:32 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mk_env(int *idx, char **string, char **env)
{
	int		status;
	char	*str[4];
	char	*env_val;
	char	*tmp;

	make_strings(idx, string, str);
	if ((*string)[*idx + 1] && (*string)[*idx + 1] == '?')
	{
		str[3] = ft_strdup(ft_itoa(WEXITSTATUS(status)));
		str[2] = ft_strdup(*string + *idx + 2);
	}
	else
	{
		env_val = get_envval(str[1] + 1, env);
		if (env_val)
			str[3] = env_val;
		else
			str[3] = ft_strdup("");
	}
	tmp = ft_strjoin(str[0], str[3]);
	*idx += ft_strlen(str[3]);
	free_4str(str[0], str[1], str[3], *string);
	*string = ft_strjoin(tmp, str[2]);
	free_2str(tmp, str[2]);
}

static t_tree_node	*apply_in_tree(t_tree_node *node, t_tree_node *head)
{
	char	*tmp;
	char	*remov;
	int		i;

	tmp = ft_strdup("\0");
	i = 0;
	while (head->token->str_info[i].str_type != NUL)
	{
		remov = tmp;
		tmp = ft_strjoin(tmp, head->token->str_info[i].str);
		free(remov);
		i++;
	}
	return (node->next);
}

void	change_env(t_tree_node *parent, char **env)
{
	int			i[2];
	t_tree_node	*n[2];

	n[0] = parent->child_list;
	while (n[0])
	{
		n[1] = n[0];
		i[0] = 0;
		while (n[0]->token->str_info[i[0]].str_type != NUL)
		{
			if (n[0]->token->str_info[i[0]].str_type != SINGLE_QUOTE)
			{
				i[1] = 0;
				while (n[0]->token->str_info[i[0]].str[i[1]])
				{
					if (n[0]->token->str_info[i[0]].str[i[1]] != '$')
						i[1]++;
					else
						mk_env(&i[1], &n[0]->token->str_info[i[0]].str, env);
				}
			}
			i[0]++;
		}
		n[0] = apply_in_tree(n[0], n[1]);
	}
}
