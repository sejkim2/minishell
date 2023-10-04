/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:32:26 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/27 15:55:45 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**add_export(char *av, char **env)
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
	renv[j] = av;
	renv[j + 1] = NULL;
	return (renv);
}

int	set_export(char **argv, char **env)
{
	int		error_code;

	error_code = check_key_rule(argv, &env);
	list_export(env);
	return (error_code);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**env;

// 	atexit(f);
// 	env = init_environ(envp);
// 	if (argc == 1 || strcmp(argv[1], "export"))
// 		return (printf("error\n"));
// 	if (argc == 2)
// 		list_export(env);
// 	else
// 		set_env(argv + 2, env);
// 	exit(0);
// }
