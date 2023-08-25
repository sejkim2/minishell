/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sejkim2 <sejkim2@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:36:45 by sejkim2           #+#    #+#             */
/*   Updated: 2023/05/25 17:08:18 by sejkim2          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

static t_nd	*init_node(int fd)
{
	t_nd	*new;

	new = (t_nd *)malloc(sizeof(t_nd));
	if (new == 0)
		return (0);
	new->fd = fd;
	new->buf = (char *)malloc(sizeof(char));
	if (new->buf == 0)
	{
		free(new);
		return (0);
	}
	new->buf[0] = '\0';
	new->next = 0;
	new->prev = 0;
	return (new);
}

static t_nd	*find_fd_and_make_node(int fd, t_nd **head)
{
	t_nd	*cur;
	t_nd	*new;

	if (*head == 0)
	{
		*head = init_node(fd);
		return (*head);
	}
	cur = *head;
	while (cur->fd != fd && cur->next != 0)
		cur = cur->next;
	if (cur->fd == fd)
		return (cur);
	new = init_node(fd);
	if (new == 0)
		return (0);
	cur->next = new;
	new->prev = cur;
	return (new);
}

static char	*del_node(t_nd **head, t_nd *nd)
{
	if (nd != *head)
		nd->prev->next = nd->next;
	if (nd->next != 0)
		nd->next->prev = nd->prev;
	if (*head == nd)
		*head = nd->next;
	free(nd->buf);
	free(nd);
	return (0);
}

static int	read_line(t_nd **nd)
{
	int		read_size;
	char	*tmp;
	char	buf[BUFFER_SIZE + 1];

	while (1)
	{
		read_size = read((*nd)->fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (-1);
		if (read_size == 0)
			return (read_size);
		buf[read_size] = '\0';
		tmp = (*nd)->buf;
		(*nd)->buf = ft_strjoin_gnl((*nd)->buf, buf);
		if ((*nd)->buf == 0)
		{
			free(tmp);
			return (-1);
		}
		free(tmp);
		if (ft_strchr_gnl(buf, '\n') != 0)
			return (read_size);
	}
}

char	*get_next_line(int fd)
{
	static t_nd		*head;
	char			*line;
	t_nd			*nd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	nd = find_fd_and_make_node(fd, &head);
	if (nd == 0)
		return (0);
	if (nd->buf == 0)
		return (del_node(&head, nd));
	if (ft_strchr_gnl(nd->buf, '\n') == 0)
	{
		if (read_line(&nd) == -1)
			return (del_node(&head, nd));
	}
	line = split_two_str(&(nd->buf));
	if (line == 0)
		return (del_node(&head, nd));
	if (line[0] == 0)
	{
		free(line);
		return (del_node(&head, nd));
	}
	return (line);
}
