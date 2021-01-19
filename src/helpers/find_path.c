/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:25:20 by alkapolly         #+#    #+#             */
/*   Updated: 2020/08/13 16:53:32 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_find_path(char *parent, t_file *file, int is_dir, int print)
{
	char	*full_path;
	char	*tmp;

	if (!(full_path = ft_strdup(file->name)))
		return (NULL);
	if (is_dir)
	{
		tmp = full_path;
		if (!(full_path = ft_strjoin(full_path, "/")))
			return (NULL);
		ft_strdel(&tmp);
	}
	if (parent && (!ft_strequ(parent, file->name)))
	{
		tmp = full_path;
		if (!(full_path = ft_strjoin(parent, tmp)))
			return (NULL);
		ft_strdel(&tmp);
	}
	if (parent && !ft_strequ(full_path, "./") && print)
		ft_printf("\n%s:", full_path);
	ft_strdel(&tmp);
	return (full_path);
}
