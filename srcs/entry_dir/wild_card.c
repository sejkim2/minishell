/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:46:30 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/16 17:59:03 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	directory는 4번, file은 8번.
	wild_card가 1이면 성공, 0이면 실패.
*/

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

// int	main(void)
// {
// 	DIR *dir;
// 	char *input;
// 	struct dirent *entry;

// 	input = readline(0);
// 	if ((dir = opendir(".")) == NULL)
// 	{
// 		perror("디렉토리 열기 실패");
// 		return (1);
// 	}
// 	while ((entry = readdir(dir)) != NULL)
// 		if (wild_card(input, entry->d_name))
// 			printf("wild: %s\n", entry->d_name);
// 	closedir(dir);
// 	return (0);
// }
