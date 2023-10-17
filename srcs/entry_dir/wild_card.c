/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:46:30 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/17 12:51:00 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	directory는 4번, file은 8번.
	wild_card가 1이면 성공, 0이면 실패.
*/

char	*wild_card_in_redir(char *redir_name, t_tree_node *child)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
	{
		perror("error\n");
		exit(1);
	}
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (wild_card(redir_name, entry->d_name))
			printf("wild: %s\n", entry->d_name);
	}
	closedir(dir);
	return (0);
}


static int	three_case(char **input, char **file)
{
	int		idx;
	char	*tmp;

	idx = 0;
	while (**input == '*')
		(*input)++;
	while ((*input)[idx] && (*input)[idx] != '*')
		idx++;
	tmp = ft_substr(*input, 0, idx);
	if (!tmp)
		exit(0);
	if (!*tmp)
	{
		free(tmp);
		return (1);
	}
	*file = strstr(*file, tmp);
	free(tmp);
	if (!*file)
		return (2);
	return (3);
}

int	wild_card(char *input, char *file)
{
	int		result;

	while (*input == *file || *input == '*')
	{
		while (*input && *file && (*input == *file))
		{
			input++;
			file++;
		}
		if (*input == '*')
		{
			result = three_case(&input, &file);
			if (result == 1)
				return (1);
			else if (result == 2)
				return (0);
		}
		if (!*input || !*file)
			break ;
	}
	if (*input != *file)
		return (0);
	return (1);
}

