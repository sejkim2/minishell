/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:04:23 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/28 15:18:49 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_pwd(void)
{
	char	buff[PATH_MAX];

	g_exit_status = 0;
	getcwd(buff, PATH_MAX);
	write(1, buff, ft_strlen(buff));
	write(1, "\n", 1);
}
