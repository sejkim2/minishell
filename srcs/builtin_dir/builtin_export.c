/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:32:26 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/10 11:52:11 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(int i, char *env_name, char *env_val, char **envp)
{
	int		j;

	j = 0;
	write(1, "declare -x ", 12);
	write(1, env_name, ft_strlen(env_name));
	if (is_equal(envp[i]))
	{
		write(1, "=\"", 2);
		while (env_val[j])
		{
			if (env_val[j] == '\"' || env_val[j] == '$')
				write(1, "\\", 1);
			write(1, &env_val[j], 1);
			j++;
		}
		write(1, "\"", 1);
	}
	printf("\n");
}

int	list_export(char **envp)
{
	int		cnt;
	int		i;
	char	*env_name;
	char	*env_val;

	cnt = cnt_line(envp);
	sort_ascii(envp, cnt);
	i = 0;
	while (i < cnt)
	{
		env_name = get_envname(envp[i]);
		env_val = get_envval(env_name, envp);
		print_export(i, env_name, env_val, envp);
		free_2str(env_name, env_val);
		i++;
	}
	return (0);
}

char	**add_export(char *str, char **env)
{
	int		i;
	int		j;
	int		cnt;
	char	**renv;

	i = 0;
	j = 0;
	cnt = cnt_line(env);
	renv = (char **)malloc(sizeof(char *) * (cnt + 2));
	while (i < cnt)
	{
		renv[j] = env[i];
		i++;
		j++;
	}
	renv[j] = str;
	renv[j + 1] = NULL;
	return (renv);
}

int	set_export(t_tree_node *child, char **env)
{
	int		error_code;

	error_code = check_key_rule(child, &env);
	list_export(env);
	return (error_code);
}

void	builtin_export(t_tree_node *parent, char **env)
{
	t_tree_node	*child;

	child = parent->child_list;
	if (child->num_of_child == 1)
		list_export(env);
	else
		set_export(child->next, env);
	exit(0);
}
