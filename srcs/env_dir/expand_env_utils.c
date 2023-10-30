/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 08:25:18 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/30 20:37:18 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*apply_in_tree(t_tree_node *node)
{
	char	*tmp;
	char	*remov;
	int		i;

	tmp = check_redir(node);
	i = 0;
	while (node->token->str_info[i].str_type != NUL)
	{
		remov = tmp;
		tmp = ft_strjoin(tmp, node->token->str_info[i].str);
		check_malloc_fail(tmp);
		free(remov);
		i++;
	}
	free(node->token->value);
	node->token->value = 0;
	return (tmp);
}

void	parser_env_in_tree(t_tree_node *parent, char **env)
{
	int			i;
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
				child->token->str_info[i].str = parser_env(child->token->str_info[i].str, env);
			i++;
		}
		child->token->value = apply_in_tree(child);
		child = child->next;
	}
}

char	*check_redir(t_tree_node *node)
{
	char	*tmp;

	if (node->token->redir_type == SINGLE_REDIR)
	{
		if (node->token->value[0] == '<')
			tmp = ft_strdup("<");
		else
			tmp = ft_strdup(">");
	}
	else if (node->token->redir_type == DOUBLE_REDIR)
	{
		if (node->token->value[0] == '<')
			tmp = ft_strdup("<<");
		else
			tmp = ft_strdup(">>");
	}
	else
		tmp = ft_strdup("");
	return (tmp);
}
