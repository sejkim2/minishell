/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:28:08 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/27 17:33:31 by jaehyji          ###   ########.fr       */
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

int	func_cd(char **argv)
{
	char	buff[PATH_MAX];
	int		error_code;
	int		cnt;

	cnt = cnt_line(argv);
	error_code = 0;
	getcwd(buff, PATH_MAX);
	printf("현재 경로: %s\n", buff);
	if (cnt == 0)
		chdir(getenv("HOME"));
	else
		error_code = chdir(argv[0]);
	if (error_code == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", argv[0]);
		exit(1);
	}
	getcwd(buff, PATH_MAX);
	return (0);
}
