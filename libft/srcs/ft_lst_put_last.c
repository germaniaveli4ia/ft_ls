/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_put_last.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 15:29:01 by cblasphe          #+#    #+#             */
/*   Updated: 2020/01/11 20:14:19 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_put_last(t_list *lst, void *content)
{
	t_list	*tmp;
	t_list	*last;

	tmp = ft_lstnew(content, ft_strlen((const char *)content));
	if (lst == NULL)
		lst = tmp;
	else
	{
		last = ft_lstlast(lst);
		last->next = tmp;
	}
	return (lst);
}
