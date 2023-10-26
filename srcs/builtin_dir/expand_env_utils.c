/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 08:25:18 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/26 19:00:41 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*apply_in_tree(t_tree_node *node, t_tree_node *head)
{
	char	*tmp;
	char	*remov;
	int		i;

	tmp = check_redir(node);
	i = 0;
	while (head->token->str_info[i].str_type != NUL)
	{
		remov = tmp;
		tmp = ft_strjoin(tmp, head->token->str_info[i].str);
		free(remov);
		i++;
	}
	free(node->token->value);
	node->token->value = 0;
	return (tmp);
}

int	dollar_string(char *str)
{
	while (*str && *str != '$')
		str++;
	while (*str)
	{
		if (*str != '$')
			return (0);
		str++;
	}
	return (1);
}

void	parser_env(int i, t_tree_node *child, char **env)
{
	int		j;

	j = 0;
	while (child->token->str_info[i].str[j])
	{
		if (dollar_string(child->token->str_info[i].str))
			break ;
		if (child->token->str_info[i].str[j] != '$')
			j++;
		else
			make_env(&j, &child->token->str_info[i].str, env);
	}
}
