/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 15:55:28 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 20:17:08 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <dirent.h>
# include <stdint.h>
# include "libft.h"
# include <pwd.h>
# include <grp.h>
# include <errno.h>
# include <stdio.h>
# include <time.h>

# define SIXMONTHS	15552000
# define FORMAT_LONG  'l'
# define FORMAT_COMMAS 'm'
# define FORMAT_ONE_COL '1'

typedef struct		s_file
{
	char			*name;
	struct stat		statb;
	struct s_file	*next;
}					t_file;

typedef	struct		s_flags
{
	short int		req;
	short int		rev;
	short int		all;
	char			format;
	short int		t;
	short int		s;
	short int		cpath;
}					t_flags;

typedef	struct		s_size
{
	size_t			link;
	size_t			user;
	size_t			group;
	size_t			size;
	size_t			major;
	size_t			minor;
	size_t			name;
	size_t			special;
	size_t			maxsize;
}					t_size;

typedef struct dirent	t_dirent;

/*
** init lists and structures
*/

t_file				*init_file();
t_size				*init_size();
void				reset_size(t_size *size);
t_flags				*init_flags();

/*
** parse flags and paths
*/

void				ft_parse_options(const char *src, t_flags *flags,
																t_size *size);
void				ft_parse_and_process_args(char **argv, t_flags *flags,
																t_size *size);
void				ft_parse_size(t_file *file, t_size *size);
char				*ft_find_path(char *parent, t_file *file, int is_dir,
																	int print);

/*
** sort files and directories
*/

void				ft_merge_sort(t_file **head, t_flags *flags);
void				ft_merge_rev_sort(t_file **head);
t_file				*time_sort(t_file *start, t_file *half, t_flags *flags);
t_file				*eventimesort(t_file *start, t_file *half, t_flags *flags);
t_file				*size_sort(t_file *start, t_file *half, t_flags *flags);
t_file				*alpha_sort(t_file *start, t_file *half, t_flags *flags);

/*
** process files and directories
*/

void				ft_process_filelist(t_file *file, t_flags *flags,
													t_size *size, size_t len);
int					ft_process_dir(char *parent, t_file *file, t_flags *flags,
																t_size *size);
void				ft_process_nonex(t_file *nonex);
int					ft_process_subdirs(char *parent, t_file *subfiles,
												t_flags *flags, t_size *size);
t_file				*ft_find_subfiles(char *full_path, t_flags *flags,
														t_size *size, DIR *dir);
void				ft_get_file_info(t_file *file, char *name);

/*
** print with options
*/

void				ft_print_all(char *parent, t_file *subfiles,
												t_flags *flags, t_size *size);
void				ft_print_blocks(t_file	*file);
void				ft_print_long(char *parent, t_file *file, t_size *size);
void				ft_print_name(char *parent, t_file *file, mode_t mode);
void				ft_print_chmod(mode_t mode);
void				ft_print_type(mode_t mode);
void				ft_print_size_or_dev(struct stat statbuf, t_size *size);
void				ft_print_time(time_t modtime);

/*
** handle errors
*/

void				ft_usage(const char *c, t_flags *flags, t_size *size);
void				ft_nodir(char *name, t_flags *flags, t_size *size);
void				ft_error(t_file *file, t_flags *flags, t_size *size);
void				ft_error_all(t_file *file, t_file *dir, t_flags *flags,
																t_size *size);

/*
** clean-up and list management
*/

void				ft_file_append(t_file **alst, t_file *new);
size_t				ft_list_len(t_file *file);
void				ft_clear_all(t_file **alst);
void				ft_clear_element(t_file **file);

#endif
