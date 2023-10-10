/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:28:08 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/10 14:47:11 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	옵션없는 cd 구현.
	cd는 인자로 절대 & 상대 경로를 받음.
	경로가 여러개일 경우, 첫 번째 인자만 인자로 인정되고 다른 것들은 무시.
	첫 번째 인자의 옳고 그름만 따짐.
	Done.
*/

void	builtin_cd(t_tree_node *parent, char **env)
{
	char		buff[PATH_MAX];
	t_tree_node	*child;

	child = parent->child_list;
	child = child->next;
	if (child->num_of_child == 1)
	{
		if (chdir(get_envval("HOME", env)) == -1)
		{
			printf("minishell: cd: HOME not set");
			exit(1);
		}
	}
	else
	{
		if (chdir(child->token->value) == -1)
		{
			printf("minishell: cd: %s: No such file or directory\n", \
			child->token->value);
			exit(1);
		}
	}
	exit(0);
}
