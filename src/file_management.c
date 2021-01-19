/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:26:00 by alkapolly         #+#    #+#             */
/*   Updated: 2020/08/13 00:26:09 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_file_append(t_file **alst, t_file *new)
{
	t_file	*save;

	save = *alst;
	if (!save)
	{
		*alst = new;
		return ;
	}
	while (save->next)
		save = save->next;
	save->next = new;
}

size_t	ft_list_len(t_file *file)
{
	t_file	*save;
	size_t	len;

	len = 0;
	save = file;
	while (save)
	{
		save = save->next;
		len++;
	}
	return (len);
}

void	ft_clear_element(t_file **file)
{
	if (!file || !*file)
		return ;
	if (*file)
	{
		if ((*file)->name)
			ft_strdel(&(*file)->name);
		free(*file);
		*file = NULL;
	}
}

void	ft_clear_all(t_file **alst)
{
	t_file	*lst;
	t_file	*save;

	lst = *alst;
	if (!lst)
		return ;
	while (lst)
	{
		save = lst;
		lst = lst->next;
		ft_clear_element(&save);
	}
	*alst = NULL;
}
