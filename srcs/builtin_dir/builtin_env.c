/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:06:44 by jaehyji           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/11 14:22:54 by jaehyji          ###   ########.fr       */
=======
/*   Updated: 2023/10/11 11:32:02 by jaehyji          ###   ########.fr       */
>>>>>>> 2f9b9d362b64dd3428ffe6cf966a75acb6812eac
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	list_env(char **envp)
{
	int		idx;

	idx = 0;
	while (envp[idx])
	{
		printf("%s\n", envp[idx]);
		idx++;
	}
}

static void	list_shv(t_tree_node *child)
{
	while (child)
	{
		if (ft_strchr(child->token->value, '='))
			printf("%s\n", child->token->value);
		child = child->next;
	}
}

static void	set_env(t_tree_node *child, char **envp)
{
	t_tree_node	*head;
	int			i;

	head = child;
	while (child->token->value)
	{
		i = 0;
		if (child->token->value[i] == '=')
		{
			printf("env: setenv %s: Invalid argument\n", child->token->value);
			exit(1);
		}
		while (child->token->value[i] && child->token->value[i] != '=')
			i++;
		if (child->token->value[i] == '\0')
		{
			printf("env: %s: No such file or directory\n", child->token->value);
			exit(127);
		}
		child = child->next;
	}
	list_env(envp);
	list_shv(head);
}

void	builtin_env(t_tree_node *parent, char **env)
{
	t_tree_node	*child;

	child = parent->child_list;
	if (child->num_of_child == 1)
		list_env(env);
	else
		set_env(child->next, env);
	exit(0);
}
