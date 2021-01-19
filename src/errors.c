/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:25:40 by alkapolly         #+#    #+#             */
/*   Updated: 2020/08/13 20:37:59 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_usage(const char *c, t_flags *flags, t_size *size)
{
	write(2, "ft_ls: illegal option -- ", 25);
	write(2, c, 1);
	write(2, "\n", 1);
	write(2, "usage: ft_ls [-1almrRtSc] [file ...]\n", 37);
	if (flags)
		free(flags);
	if (size)
		free(size);
	exit(EXIT_FAILURE);
}

void	ft_nodir(char *name, t_flags *flags, t_size *size)
{
	write(2, "ft_ls: ", 7);
	write(2, name, ft_strlen(name));
	write(2, ": No such file or directory\n", 28);
	if (flags)
		free(flags);
	if (size)
		free(size);
	exit(EXIT_FAILURE);
}

void	ft_error(t_file *file, t_flags *flags, t_size *size)
{
	perror("ft_ls");
	if (file)
		ft_clear_all(&file);
	if (flags)
		free(flags);
	if (size)
		free(size);
	exit(EXIT_FAILURE);
}

void	ft_error_all(t_file *file, t_file *dir, t_flags *flags, t_size *size)
{
	perror("ft_ls");
	if (file)
		ft_clear_all(&file);
	if (dir)
		ft_clear_all(&dir);
	if (flags)
		free(flags);
	if (size)
		free(size);
	exit(EXIT_FAILURE);
}
