/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:26:18 by alkapolly         #+#    #+#             */
/*   Updated: 2020/08/13 19:49:21 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*init_file(void)
{
	t_file *file;

	if (!(file = (t_file *)ft_memalloc(sizeof(t_file))))
		return (NULL);
	file->name = NULL;
	file->next = NULL;
	return (file);
}

t_flags	*init_flags(void)
{
	t_flags *flags;

	if (!(flags = (t_flags *)ft_memalloc(sizeof(t_flags))))
		return (NULL);
	flags->all = 0;
	flags->req = 0;
	flags->rev = 0;
	flags->t = 0;
	flags->s = 0;
	flags->format = 0;
	flags->cpath = 0;
	return (flags);
}

void	reset_size(t_size *size)
{
	size->link = 0;
	size->user = 0;
	size->group = 0;
	size->size = 0;
	size->major = 0;
	size->minor = 0;
	size->name = 0;
	size->special = 0;
	size->maxsize = 0;
}

t_size	*init_size(void)
{
	t_size *size;

	if (!(size = (t_size *)ft_memalloc(sizeof(t_size))))
		return (NULL);
	reset_size(size);
	return (size);
}
