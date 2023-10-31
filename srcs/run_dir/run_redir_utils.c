/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 17:34:00 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/31 20:12:37 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_redir_file_name(t_tree_node *node)
{
	char	*file_name;
	char	*remove_str;
	int		i;

	i = 0;
	file_name = ft_strdup("");
	while (node->token->str_info[i].str_type != NUL)
	{
		remove_str = file_name;
		file_name = ft_strjoin(file_name, node->token->str_info[i].str);
		free_str(remove_str);
		i++;
	}
	return (file_name);
}

int	wild_card_error(char *input, int cnt)
{
	if (cnt > 1)
	{
		write(2, "minishell: ", 12);
		write(2, input, 8);
		write(2, ": ", 3);
		write(2, "ambiguous redirect\n", 20);
	}
	g_exit_status = 1;
	return (-1);
}

int	open_error(char *redir_name)
{
	ft_stderror_print(redir_name, NULL, strerror(errno));
	return (-1);
}
