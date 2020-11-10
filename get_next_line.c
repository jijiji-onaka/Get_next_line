/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 23:19:23 by sehattor          #+#    #+#             */
/*   Updated: 2020/11/10 18:06:32 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl	*gnl_lstnew(char *content, int fd)
{
	t_gnl	*new_element;

	if (!(new_element = malloc(sizeof(t_gnl))))
		return (NULL);
	new_element->fd = fd;
	new_element->store = ft_strdup(content);
	new_element->next = NULL;
	return (new_element);
}

static void		gnl_lstadd_front(t_gnl **lst, t_gnl *new)
{
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}

static t_gnl	*recognize_fd(int fd, t_gnl **lst)
{
	t_gnl			*res;

	res = *lst;
	while (res)
	{
		if (res->fd == fd)
			return (res);
		res = res->next;
	}
	res = gnl_lstnew("", fd);
	gnl_lstadd_front(lst, res);
	return (res);
}

int				get_next_line(int fd, char **line)
{
	static t_gnl	*lst;
	t_gnl			*now;
	char			*buf;
	char			*newline;
	char			*tmp;
	int				rc;

	*line = NULL;
	if (fd < 0 || !line || (!(now = recognize_fd(fd, &lst))) \
		|| (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1)))))
		return (-1);
	while ((!(newline = ft_strchr(now->store, '\n'))) && (rc = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[rc] = '\0';
		tmp = now->store;
		now->store = ft_strjoin(now->store, buf);
		free(tmp);
		if (!(now->store))
			return (-1);
	}
	free(buf);
	if (rc < 0)
		return (-1);
	if (newline != NULL)
	{
		*line = ft_substr(now->store, 0, newline - now->store);
		char *tmp = now->store;
		now->store = ft_strdup(newline + 1);
		free(tmp);
		if (*line == NULL)
			return (-1);
		return (1);
	}
	*line = ft_strdup(now->store);
	free(now->store);
	now->store = NULL;
	if (*line == NULL)
		return (-1);
	return (0);
}
