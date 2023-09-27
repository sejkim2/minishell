/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:21:43 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/27 17:23:54 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char** environ;

int	main(void)
{
	char	*line;
	char	**ptr;
	char	**rptr;

	while (1)
	{
		line = readline("input> ");
		ptr = ft_split(line, ' ');
		rptr = change_env(ptr, environ);

	}
}
