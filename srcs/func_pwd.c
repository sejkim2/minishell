/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:04:23 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/12 16:21:47 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	char	buff[PATH_MAX];

	if (argc != 2 || strcmp("pwd", argv[1]))
		return (printf("error\n"));
	getcwd(buff, PATH_MAX);
	printf("%s\n", buff);
}
