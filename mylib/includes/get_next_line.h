/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:36:39 by sejkim2           #+#    #+#             */
/*   Updated: 2023/05/25 17:02:40 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_nd
{
	int				fd;
	char			*buf;
	struct s_nd		*next;
	struct s_nd		*prev;
}	t_nd;

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
size_t	ft_strlen_gnl(const char *s);
char	*get_next_line(int fd);
char	*split_two_str(char **buf);
char	*ft_strchr_gnl(const char *s, int c);

#endif
