/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:32:26 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/19 19:23:28 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	list_export(char **envp)
{
	int		cnt;
	int		idx;
	char	*env_name;
	char	*env_val;

	cnt = cnt_line(envp);
	sort_ascii(envp, cnt);
	idx = 0;
	while (idx < cnt)
	{
		env_name = get_envname(envp[idx]);
		env_val = get_envval(env_name, envp);
		printf("declare -x %s", env_name);
		if (is_equal(envp[idx]))
			printf("=\"%s\"", env_val);
		printf("\n");
		free_2str(env_name, env_val);
		idx++;
	}
	return (0);
}

int	set_env(char **argv, char **env)
{
	int		error_code;

	error_code = check_key_rule(argv, &env);
	list_export(env);
	return (error_code);
}

int	main(int argc, char **argv, char **envp)
{
	char	**env;

	env = init_environ(envp);
	if (argc == 1 || strcmp(argv[1], "export"))
		return (printf("error\n"));
	if (argc == 2)
		return (list_export(envp));
	else
		return (set_env(argv + 2, env));
}
