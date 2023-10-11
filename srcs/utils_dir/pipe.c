/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:43:32 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/11 11:44:57 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fd	init_fd_struct(void)
{
	t_fd	ret;

	ret.iput[0] = 0;
	ret.iput[1] = 0;
	ret.oput[0] = 0;
	ret.oput[1] = 0;
}
