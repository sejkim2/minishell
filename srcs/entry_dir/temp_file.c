/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehyji <jaehyji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:24:41 by jaehyji           #+#    #+#             */
/*   Updated: 2023/10/18 15:37:46 by jaehyji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	작업 히스토리는 bash가 종료됐을 때 기록이 반영 됨.
	임시 파일을 하나 만들고 minishell이 종료되었을 때 임시 파일의 내용을 히스토리로 옮김.
*/

char	*generate_temp_filename(char *mode)
{
	char	*str;
	char	*rstr;
	int		i;

	str = ft_strdup(mode);
	if (access(str, F_OK) == -1)
		return (str);
	while (access(str, F_OK) == 0)
	{
		i = 0;
		rstr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
		ft_memcpy(rstr, str, ft_strlen(str));
		while (i < 10)
		{
			rstr[ft_strlen(str)] = i + '0';
			rstr[ft_strlen(str) + 1] = '\0';
			if (access(rstr, F_OK) == -1)
				return (free(str), rstr);
			i++;
		}
		rstr[ft_strlen(str)] = '_';
		free(str);
		str = rstr;
	}
	return (str);
}

int	here_document(void)
{
	char	*tmp_name;
	int		hd_fd;

	tmp_name = generate_temp_filename("HD_Temp");
	hd_fd = open(tmp_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(tmp_name);
	return (hd_fd);
}

void	working_history(void)
{
	char	*tmp_name;
	int		wh_fd;
	int		tp_fd;

	wh_fd = open(".minishell_history", O_RDWR | O_CREAT | O_APPEND, 0644);
	tmp_name = generate_temp_filename("WH_Temp");
	tp_fd = open(tmp_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	free(tmp_name);
}

void	filecpy(int in_fd, int out_fd)
{
	char	*line;

	line = get_next_line(in_fd);
	while (line)
	{
		write(out_fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(in_fd);
	}
}

// int	main()
// {
// 	int	fd1 = open("in", O_RDWR);
// 	int	fd2 = open("out", O_RDWR | O_CREAT | O_TRUNC, 0644);

// 	filecpy(fd1, fd2);
// 	unlink("in");
// }