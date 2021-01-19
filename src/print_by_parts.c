/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_by_parts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 20:40:28 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 17:39:30 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_name(char *parent, t_file *file, mode_t mode)
{
	char	link[1024];
	char	*path;
	char	*tmp;
	int		i;

	path = NULL;
	if (!S_ISLNK(mode))
	{
		ft_printf("%s\n", file->name);
		return ;
	}
	ft_bzero(link, 1024);
	path = ft_strdup(file->name);
	if (parent)
	{
		tmp = ft_strjoin("/", path);
		ft_strdel(&path);
		path = ft_strjoin(parent, tmp);
		ft_strdel(&tmp);
	}
	i = readlink(path, link, 1024);
	ft_strdel(&path);
	if (i < 0)
		ft_error(file, 0, 0);
	ft_printf("%s -> %s\n", file->name, link);
}

void	ft_print_chmod(mode_t mode)
{
	char	chmod[11];

	chmod[0] = (mode & S_IRUSR) ? 'r' : '-';
	chmod[1] = (mode & S_IWUSR) ? 'w' : '-';
	if (mode & S_ISUID)
		chmod[2] = (mode & S_IXUSR) ? 's' : 'S';
	else
		chmod[2] = (mode & S_IXUSR) ? 'x' : '-';
	chmod[3] = (mode & S_IRGRP) ? 'r' : '-';
	chmod[4] = (mode & S_IWGRP) ? 'w' : '-';
	if (mode & S_ISGID)
		chmod[5] = (mode & S_IXGRP) ? 's' : 'S';
	else
		chmod[5] = (mode & S_IXGRP) ? 'x' : '-';
	chmod[6] = (mode & S_IROTH) ? 'r' : '-';
	chmod[7] = (mode & S_IWOTH) ? 'w' : '-';
	if (mode & S_ISGID)
		chmod[8] = (mode & S_IXOTH) ? 't' : 'T';
	else
		chmod[8] = (mode & S_IXOTH) ? 'x' : '-';
	chmod[9] = ' ';
	chmod[10] = '\0';
	write(1, chmod, 10);
}

void	ft_print_type(mode_t mode)
{
	char	type;

	if (S_ISFIFO(mode))
		type = 'p';
	else if (S_ISCHR(mode))
		type = 'c';
	else if (S_ISDIR(mode))
		type = 'd';
	else if (S_ISBLK(mode))
		type = 'b';
	else if (S_ISLNK(mode))
		type = 'l';
	else if (S_ISSOCK(mode))
		type = 's';
	else
		type = '-';
	ft_printf("%c", type);
}

void	ft_print_size_or_dev(struct stat statbuf, t_size *size)
{
	if (!size->special)
		ft_printf("%*d ", size->maxsize, statbuf.st_size);
	else if (S_ISCHR(statbuf.st_mode) || S_ISBLK(statbuf.st_mode))
	{
		(ft_numlen(major(statbuf.st_rdev)) < 4)
			? ft_printf("% 3d,", major(statbuf.st_rdev))
			: ft_printf(" %#010x,", major(statbuf.st_rdev));
		(ft_numlen(minor(statbuf.st_rdev)) < 4)
			? ft_printf("% 4d ", minor(statbuf.st_rdev))
			: ft_printf(" %#010x ", minor(statbuf.st_rdev));
	}
	else
		ft_printf("%*d ", size->maxsize, statbuf.st_size);
}

void	ft_print_time(time_t modtime)
{
	time_t	curtime;
	char	*fulltime;

	curtime = time(NULL);
	fulltime = ctime(&modtime) + 4;
	ft_printf("%.6s", fulltime);
	(curtime - modtime < SIXMONTHS || modtime > curtime)
		? ft_printf(" %.5s ", fulltime + 7)
		: ft_printf(" %.4s ", fulltime + 16);
}
