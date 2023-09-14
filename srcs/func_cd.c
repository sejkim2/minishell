/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:28:08 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/14 11:28:34 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	옵션없는 cd 구현.
	cd는 인자로 절대 & 상대 경로를 받음.
	인자가 2개 이상일 경우, 즉 경로가 여러개일 경우, 첫 번째 인자만 상관함.
	추가사항: -로 이전 경로로 되돌아가는 것은, 현재경로를 저장해서 실행하면 될 것 같음.
*/

int	main(int argc, char **argv)
{
	char	buff[PATH_MAX];
	int		error_code;

	error_code = 0;
	if (argc != 2 && argc != 3)
		return (printf("error\n"));
	change_env(argv);
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
