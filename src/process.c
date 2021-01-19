/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:26:53 by alkapolly         #+#    #+#             */
/*   Updated: 2020/08/13 20:21:05 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_process_nonex(t_file *nonex)
{
	t_flags	*flags;
	t_file	*tmp;

	tmp = nonex;
	flags = init_flags();
	ft_merge_sort(&nonex, flags);
	while (nonex)
	{
		ft_printf("ft_ls: %s: %s\n", nonex->name, strerror(errno));
		nonex = nonex->next;
	}
	free(flags);
	ft_clear_all(&tmp);
}

int		ft_process_subdirs(char *parent, t_file *subfiles, t_flags *flags,
																t_size *size)
{
	while (subfiles)
	{
		if ((S_ISDIR(subfiles->statb.st_mode))
				&& !ft_strequ(subfiles->name, ".")
				&& !ft_strequ(subfiles->name, ".."))
			ft_process_dir(parent, subfiles, flags, size);
		subfiles = subfiles->next;
	}
	return (1);
}

t_file	*ft_find_subfiles(char *full_path, t_flags *flags, t_size *size,
																	DIR *dir)
{
	t_file		*new;
	t_dirent	*ent;
	t_file		*subfiles;
	char		*path;

	subfiles = NULL;
	new = NULL;
	while ((ent = readdir(dir)))
	{
		if (!ent || (!flags->all && ent->d_name[0] == '.'))
			continue;
		new = init_file();
		if (!new)
			ft_error(subfiles, flags, size);
		new->name = ft_strdup(ent->d_name);
		path = ft_find_path(full_path, new, 0, 0);
		if (lstat(path, &(new->statb)) == -1)
			ft_error(new, flags, size);
		ft_strdel(&path);
		ft_parse_size(new, size);
		ft_file_append(&subfiles, new);
	}
	closedir(dir);
	return (subfiles);
}

int		ft_process_dir(char *parent, t_file *file, t_flags *flags, t_size *size)
{
	int			blocks;
	t_file		*subfiles;
	char		*full_path;
	DIR			*dir;

	blocks = 0;
	if (!(full_path = ft_find_path(parent, file, 1, 1)))
		ft_error(file, flags, size);
	if (!(dir = opendir(full_path)))
	{
		(parent) ? perror("\nft_ls") : perror("ft_ls");
		return (0);
	}
	subfiles = ft_find_subfiles(full_path, flags, size, dir);
	if ((!subfiles && file->next) || parent)
		ft_printf("\n");
	(flags->format == FORMAT_LONG && subfiles) ? ft_print_blocks(subfiles) : 0;
	ft_merge_sort(&subfiles, flags);
	ft_print_all(full_path, subfiles, flags, size);
	reset_size(size);
	if (flags->req && subfiles)
		ft_process_subdirs(full_path, subfiles, flags, size);
	ft_strdel(&full_path);
	ft_clear_all(&subfiles);
	return (1);
}

void	ft_process_filelist(t_file *file, t_flags *flags, t_size *size,
															size_t len)
{
	size_t	count;
	t_file	*tmp;

	count = len;
	tmp = file;
	ft_merge_sort(&file, flags);
	while (count--)
	{
		ft_parse_size(file, size);
		if (S_ISDIR(file->statb.st_mode))
		{
			if ((flags->cpath > 1 || len > 1)
			&& (!(flags->cpath == 1 && ft_strequ(file->name, "."))))
				ft_printf("%s:\n", file->name);
			ft_process_dir(NULL, file, flags, size);
			if (count != 0)
				ft_printf("\n");
		}
		else
			ft_print_all(NULL, file, flags, size);
		file = file->next;
	}
	ft_clear_all(&tmp);
}
