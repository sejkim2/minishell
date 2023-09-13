/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:27:46 by jaehyji           #+#    #+#             */
/*   Updated: 2023/09/13 20:15:02 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	change_env: 들어온 인자가 환경변수라면 해당 환경변수를 참조하여 문자열을 확장.
*/

static void	free_2str(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

char	**change_env(char **av)
{
	int		i;
	int		j;
	char	*str[3];

	i = 0;
	while (av[i])
	{
		j = 0;
		while (av[i][j] && av[i][j] != '$')
			j++;
		if (av[i][j] == '$')
		{
			str[0] = ft_substr(av[i], 0, j - 1);
			str[1] = ft_substr(av[i], j + 1, \
			ft_strlen(av[i] - ft_strlen(str[0]) - 1));
			if (getenv(str[1]))
				str[2] = getenv(str[1]);
			else
				str[2] = ft_strdup("");
			av[i] = ft_strjoin(str[0], str[2]);
			free_2str(str[0], str[2]);
		}
		i++;
	}
	return (av);
}
