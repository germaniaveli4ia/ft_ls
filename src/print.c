/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 20:40:28 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 20:41:56 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_long(char *parent, t_file *file, t_size *size)
{
	struct passwd	*pas;
	struct group	*grp;
	char			*user;
	char			*group;

	ft_print_type(file->statb.st_mode);
	ft_print_chmod(file->statb.st_mode);
	pas = getpwuid(file->statb.st_uid);
	grp = getgrgid(file->statb.st_gid);
	user = (pas) ? ft_strdup(pas->pw_name) : ft_itoa(file->statb.st_uid);
	group = (grp) ? ft_strdup(grp->gr_name) : ft_itoa(file->statb.st_gid);
	ft_printf("%*i", ((size->link < 2) ? 2 : size->link),
													file->statb.st_nlink);
	ft_printf(" %-*s", size->user, user);
	ft_printf("  %-*s  ", size->group, group);
	ft_print_size_or_dev(file->statb, size);
	ft_print_time(file->statb.st_mtime);
	ft_print_name(parent, file, file->statb.st_mode);
	ft_strdel(&user);
	ft_strdel(&group);
}

void	ft_print_one(t_file *file)
{
	ft_printf("%s\n", file->name);
}

void	ft_print_commas(t_file *file)
{
	ft_printf("%s%s", file->name, (file->next) ? ",  " : "\n");
}

void	ft_print_all(char *parent, t_file *file, t_flags *flags, t_size *size)
{
	if (file == NULL)
		return ;
	while (file)
	{
		if (flags->format == FORMAT_LONG)
			ft_print_long(parent, file, size);
		else if (flags->format == FORMAT_COMMAS)
			ft_print_commas(file);
		else if (flags->format == FORMAT_ONE_COL)
			ft_print_one(file);
		else
		{
			ft_printf("%s", file->name);
			(file->next) ? ft_printf("  ") : ft_printf("\n");
		}
		file = file->next;
	}
}

void	ft_print_blocks(t_file *file)
{
	int		blocks;

	blocks = 0;
	while (file)
	{
		blocks += file->statb.st_blocks;
		file = file->next;
	}
	ft_printf("total %zu\n", blocks);
}
