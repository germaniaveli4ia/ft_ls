/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:27:15 by alkapolly         #+#    #+#             */
/*   Updated: 2020/08/13 18:10:03 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_file	*alpha_sort(t_file *start, t_file *half, t_flags *flags)
{
	t_file	*new;

	new = NULL;
	if (start == NULL)
		return (half);
	else if (half == NULL)
		return (start);
	if ((ft_strcmp(start->name, half->name)) < 0)
	{
		new = start;
		new->next = alpha_sort(start->next, half, flags);
	}
	else
	{
		new = half;
		new->next = alpha_sort(start, half->next, flags);
	}
	return (new);
}

t_file	*size_sort(t_file *start, t_file *half, t_flags *flags)
{
	t_file	*new;

	new = NULL;
	if (start == NULL)
		return (half);
	else if (half == NULL)
		return (start);
	else if (start->statb.st_size >= half->statb.st_size)
	{
		new = start;
		new->next = size_sort(start->next, half, flags);
	}
	else
	{
		new = half;
		new->next = size_sort(start, half->next, flags);
	}
	return (new);
}

t_file	*eventimesort(t_file *start, t_file *half, t_flags *flags)
{
	t_file	*new;
	long	snsec;
	long	hnsec;

	new = NULL;
	snsec = (flags->t == 1) ? start->statb.st_mtimespec.tv_nsec
						: start->statb.st_ctimespec.tv_nsec;
	hnsec = (flags->t == 1) ? half->statb.st_mtimespec.tv_nsec
						: half->statb.st_ctimespec.tv_nsec;
	if (snsec >= hnsec)
	{
		new = start;
		new->next = time_sort(start->next, half, flags);
	}
	else
	{
		new = half;
		new->next = time_sort(start, half->next, flags);
	}
	return (new);
}

t_file	*time_sort(t_file *start, t_file *half, t_flags *flags)
{
	t_file	*new;
	time_t	ssec;
	time_t	hsec;

	if (start == NULL)
		return (half);
	else if (half == NULL)
		return (start);
	ssec = (flags->t == 1) ? start->statb.st_mtimespec.tv_sec
					: start->statb.st_ctimespec.tv_sec;
	hsec = (flags->t == 1) ? half->statb.st_mtimespec.tv_sec
					: half->statb.st_ctimespec.tv_sec;
	if (ssec == hsec)
		return (eventimesort(start, half, flags));
	else if (ssec > hsec)
	{
		new = start;
		new->next = time_sort(start->next, half, flags);
	}
	else
	{
		new = half;
		new->next = time_sort(start, half->next, flags);
	}
	return (new);
}
