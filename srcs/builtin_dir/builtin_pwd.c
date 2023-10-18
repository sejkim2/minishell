/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:04:23 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/18 15:14:35 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(char **env)
{
	char	buff[PATH_MAX];

	getcwd(buff, PATH_MAX);
	printf("%s\n", buff);
	g_exit_status = 0;
}
