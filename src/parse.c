/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 19:25:17 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 21:34:53 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_parse_size(t_file *file, t_size *size)
{
	struct passwd	*pas;
	struct group	*grp;

	pas = getpwuid(file->statb.st_uid);
	grp = getgrgid(file->statb.st_gid);
	size->link = ft_max(size->link, ft_numlen(file->statb.st_nlink));
	size->user = (pas) ? ft_max(size->user,
	ft_strlen(pas->pw_name)) : ft_max(size->user,
										ft_numlen(file->statb.st_uid));
	size->group = (grp) ? ft_max(size->group,
	ft_strlen(grp->gr_name)) : ft_max(size->group,
										ft_numlen(file->statb.st_gid));
	size->size = ft_max(size->size, ft_numlen(file->statb.st_size));
	size->major = ft_max(size->major, ft_numlen(major(file->statb.st_rdev)));
	size->minor = ft_max(size->minor, ft_numlen(minor(file->statb.st_rdev)));
	size->name = ft_max(size->name, ft_strlen(file->name));
	size->maxsize = size->size;
	if (S_ISCHR(file->statb.st_mode) || S_ISBLK(file->statb.st_mode))
		size->special = 1;
	if (size->special && size->size < 8)
		size->maxsize = 8;
}

void			ft_parse_options(const char *src, t_flags *flags, t_size *size)
{
	src++;
	if (!(*src))
		ft_nodir("-", flags, size);
	while (*src)
	{
		if (!ft_strchr("SRralm1tc-", *src))
			ft_usage(src, flags, size);
		if (*src == 'r')
			flags->rev = 1;
		else if (*src == 'R')
			flags->req = 1;
		else if (*src == 'a')
			flags->all = 1;
		else if (*src == 't')
			flags->t = 1;
		else if (*src == 'S')
			flags->s = 1;
		else if (*src == 'c')
			flags->t = 2;
		if (*src == FORMAT_LONG
				|| *src == FORMAT_ONE_COL
				|| *src == FORMAT_COMMAS)
			flags->format = *src;
		src++;
	}
}

static int		ft_fill_elem_info(t_file *file, char *argv)
{
	if (!(file->name = ft_strdup(argv)))
	{
		ft_clear_element(&file);
		ft_error(0, 0, 0);
	}
	if (lstat(file->name, &(file->statb)) == -1)
		return (-1);
	return (1);
}

static t_file	*ft_parse_args(char **argv, t_file **files, t_flags *flags,
															t_size *size)
{
	t_file	*new;
	t_file	*dirs;
	t_file	*nonex;

	new = NULL;
	dirs = NULL;
	nonex = NULL;
	while (*argv && *argv[0] == '-')
	{
		ft_parse_options(*argv, flags, size);
		argv++;
	}
	while (*argv)
	{
		if (!(new = init_file()))
			ft_error_all(*files, dirs, flags, size);
		if (ft_fill_elem_info(new, *argv) == 1)
			ft_file_append(S_ISDIR(new->statb.st_mode) ? &dirs : files, new);
		else
			ft_file_append(&nonex, new);
		flags->cpath++;
		argv++;
	}
	(nonex) ? ft_process_nonex(nonex) : 0;
	return (dirs);
}

void			ft_parse_and_process_args(char **argv, t_flags *flags,
															t_size *size)
{
	t_file	*filelist;
	t_file	*dirlist;

	filelist = NULL;
	dirlist = ft_parse_args(argv, &filelist, flags, size);
	if (!flags->cpath)
	{
		if (!(dirlist = init_file()))
			ft_error(dirlist, flags, size);
		ft_fill_elem_info(dirlist, ".");
	}
	if (filelist)
		ft_process_filelist(filelist, flags, size, 1);
	if (filelist && dirlist)
		ft_printf("\n");
	if (dirlist)
		ft_process_filelist(dirlist, flags, size, ft_list_len(dirlist));
}
