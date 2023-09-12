/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:28:08 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/12 16:05:25 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	char	buff[PATH_MAX];
	int		error_code;

	error_code = 0;
	if (argc != 2 && argc != 3)
		return (printf("error\n"));
	getcwd(buff, PATH_MAX);
	printf("현재 경로: %s\n", buff);
	if (!strcmp(argv[1], "cd"))
	{
		if (argc == 2)
			chdir(getenv("HOME"));
		else
			error_code = chdir(argv[2]);
		if (error_code == -1)
			exit(1);
		getcwd(buff, PATH_MAX);
		printf("이동 경로: %s\n", buff);
	}
	exit(0);
}
