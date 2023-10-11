/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:36:27 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/10 09:44:42 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	받은 인자를 문자열로 출력함.
	인자가 다수라면, 각 인자에 공백을 삽입하여 붙여 출력함.
	-n 옵션은 줄바꿈을 붙이지 않음. 따라서 프롬프트가 출력문에 바로 붙어서 들어오게 됨. 
*/

static void	echo_no_opt_print(int argc, t_tree_node *child)
{
	int		idx;

	if (argc == 0)
	{
		printf("\n");
		return ;
	}
	idx = 0;
	while (idx < argc)
	{
		printf("%s", child->token->value);
		if (idx < argc - 1)
			printf(" ");
		idx++;
		child = child->next;
	}
	printf("\n");
	return ;
}

static void	echo_opt_print(int argc, t_tree_node *child)
{
	int		idx;

	idx = 0;
	while (idx < argc)
	{
		printf("%s", child->token->value);
		if (idx < argc - 1)
			printf(" ");
		idx++;
		child = child->next;
	}
	return ;
}

static int	echo_opt_flag(char *str)
{
	int		idx;

	idx = 1;
	if (str[idx] == '\0')
		return (0);
	while (str[idx] && str[idx] == 'n')
		idx++;
	if (str[idx] != '\0')
		return (0);
	return (1);
}

static void	echo_opt(int argc, t_tree_node *child)
{
	int		i;
	int		j;

	i = 0;
	if (echo_opt_flag(child->token->value))
	{
		while (child->token->value[0] == '-')
		{
			j = 1;
			if (!child->token->value[j])
				break ;
			while (child->token->value[j])
			{
				if (child->token->value[j] == 'n')
					j++;
				else
					return (echo_opt_print(argc - i, child));
			}
			child = child->next;
			i++;
		}
		return (echo_opt_print(argc - i, child));
	}
	else
		return (echo_no_opt_print(argc, child));
}

void	builtin_echo(t_tree_node *parent, char **env)
{
	t_tree_node	*child;

	child = parent->child_list;
	child = child->next;
	if (!child->next || child->token->value[0] != '-')
		echo_no_opt_print(child->num_of_child - 1, child->next);
	else
		echo_opt(child->num_of_child - 1, child->next);
	exit(0);
}
