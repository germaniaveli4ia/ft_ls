/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 18:52:37 by cblasphe          #+#    #+#             */
/*   Updated: 2019/12/14 14:46:59 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strdup_till(char **dst, const char *src, char break_symbol)
{
	int	break_pos;

	break_pos = ft_strchr_pos(src, break_symbol);
	if (break_pos < 0)
		break_pos = ft_strlen(src);
	*dst = ft_strndup(src, break_pos);
	if (!*dst)
		return (0);
	return (break_pos);
}

int		ft_read(int fd, char **content)
{
	int		read_size;
	char	buf[BUFF_SIZE + 1];
	char	*old_content;

	while ((read_size = read(fd, buf, BUFF_SIZE)))
	{
		buf[read_size] = '\0';
		old_content = *content;
		*content = ft_strjoin(*content, buf);
		if (!*content)
			return (-1);
		ft_strdel(&old_content);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (read_size);
}

t_list	*ft_get_session(int fd, t_list **sessions)
{
	t_list	*tmp;

	if (!sessions)
		return (NULL);
	tmp = *sessions;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", fd);
	ft_lstadd(sessions, tmp);
	return (*sessions);
}

int		fd_valid(int fd)
{
	char	buff[1];

	return (fd >= 0 && read(fd, buff, 0) == 0);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*sessions;
	t_list			*session;
	char			*cur_text;
	int				read_res;

	if (!fd_valid(fd) || !line || !(session = ft_get_session(fd, &sessions)))
		return (-1);
	cur_text = session->content;
	read_res = ft_read(fd, &cur_text);
	session->content = cur_text;
	if (!read_res && !*cur_text)
		return (0);
	read_res = ft_strdup_till(line, cur_text, '\n');
	if (!cur_text[read_res])
		cur_text[0] = '\0';
	else
	{
		session->content = ft_strdup(ft_strchr(cur_text, '\n') + 1);
		ft_strdel(&cur_text);
	}
	return (1);
}
