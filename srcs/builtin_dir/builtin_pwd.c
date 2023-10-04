/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:04:23 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/27 15:39:12 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	옵션없는 pwd구현.
	pwd는 인자를 받지 않음. 인자 개수의 상관없이 pwd는 출력을 진행함.
*/

// int	main(int argc, char **argv)
// {
// 	char	buff[PATH_MAX];

// 	if (argc != 2 || strcmp("pwd", argv[1]))
// 		return (printf("error\n"));
// 	getcwd(buff, PATH_MAX);
// 	printf("%s\n", buff);
// }
