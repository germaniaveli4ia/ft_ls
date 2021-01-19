/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:27:04 by alkapolly         #+#    #+#             */
/*   Updated: 2020/08/13 16:41:53 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	find_end(t_file *head, t_file **start, t_file **end)
{
	t_file *fast;
	t_file *slow;

	slow = head;
	fast = head->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*end = slow->next;
	*start = head;
	slow->next = NULL;
}

void		ft_merge_rev_sort(t_file **head)
{
	t_file	*cur;
	t_file	*next;
	t_file	*prev;

	cur = *head;
	next = NULL;
	prev = next;
	while (cur)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*head = prev;
}

static void	merge_sort2(t_file **head, t_flags *flags,
								t_file *(*f)(t_file *, t_file *, t_flags *))
{
	t_file	*start;
	t_file	*half;
	t_file	*save;

	save = *head;
	if (save == NULL || save->next == NULL)
		return ;
	find_end(save, &start, &half);
	merge_sort2(&start, flags, f);
	merge_sort2(&half, flags, f);
	*head = f(start, half, flags);
}

void		ft_merge_sort(t_file **head, t_flags *flags)
{
	merge_sort2(head, flags, &alpha_sort);
	if (flags->t && !flags->s)
		merge_sort2(head, flags, &time_sort);
	if (flags->s)
		merge_sort2(head, flags, &size_sort);
	if (flags->rev)
		ft_merge_rev_sort(head);
}
