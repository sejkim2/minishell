/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 08:25:18 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/18 15:27:58 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mk_env(int *idx, char **string, char **env)
{
	int		status;
	char	*str[4];
	char	*env_val;
	char	*tmp;

	make_strings(idx, string, str);
	if ((*string)[*idx + 1] && (*string)[*idx + 1] == '?')
	{
		str[3] = ft_strdup(ft_itoa((int)g_exit_status));
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

t_tree_node	*apply_in_tree(t_tree_node *node, t_tree_node *head)
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
	node->token->value = tmp;
	return (node->next);
}

int	dollar_string(char *str)
{
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
			mk_env(&j, &child->token->str_info[i].str, env);
	}
}
