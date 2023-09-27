/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:28:08 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/25 21:02:23 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	옵션없는 cd 구현.
	cd는 인자로 절대 & 상대 경로를 받음.
	경로가 여러개일 경우, 첫 번째 인자만 인자로 인정되고 다른 것들은 무시.
	첫 번째 인자의 옳고 그름만 따짐.
	추가사항: -로 이전 경로로 되돌아가는 것은, 현재경로를 저장해서 실행하면 될 것 같음.
	Done.
*/

// int	main(int argc, char **argv, char **envp)
// {
// 	char	buff[PATH_MAX];
// 	int		error_code;

// 	error_code = 0;
// 	if (argc == 1)
// 		return (printf("error\n"));
// 	change_env(argv, envp);
// 	getcwd(buff, PATH_MAX);
// 	printf("현재 경로: %s\n", buff);
// 	if (!strcmp(argv[1], "cd"))
// 	{
// 		if (argc == 2)
// 			chdir(getenv("HOME"));
// 		else
// 			error_code = chdir(argv[2]);
// 		if (error_code == -1)
// 		{
// 			printf("minishell: cd: %s: No such file or directory\n", argv[2]);
// 			exit(1);
// 		}
// 		getcwd(buff, PATH_MAX);
// 		printf("이동 경로: %s\n", buff);
// 	}
// 	exit(0);
// }
