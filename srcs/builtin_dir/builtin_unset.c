/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:42:03 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/10 10:22:43 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**rearrange_env(int cnt, char **env)
{
	int		i;
	int		j;
	char	**renv;

	i = 0;
	j = 0;
	renv = (char **)malloc(sizeof(char *) * (cnt + 1));
	while (i < cnt)
	{
		if (!env[i])
		{
			i++;
			continue ;
		}
		renv[j] = env[i];
		i++;
		j++;
	}
	renv[j] = NULL;
	free(env);
	return (renv);
}

void	builtin_unset(t_tree_node *parent, char **env)
{
	int			i;
	int			cnt;
	char		*env_name[2];
	t_tree_node	*child;

	cnt = cnt_line(env);
	child = parent->child_list;
	child = child->next;
	while (child)
	{
		i = 0;
		while (env[i])
		{
			env_name[0] = get_envname(child->token->value);
			env_name[1] = get_envname(env[i]);
			if (!strcmp(env_name[0], env_name[1]))
				env[i] = 0;
			i++;
		}
		free_2str(env_name[0], env_name[1]);
		child = child->next;
	}
	env = rearrange_env(cnt, env);
}
