/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpurge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:35:10 by cblasphe          #+#    #+#             */
/*   Updated: 2019/09/26 18:45:53 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpurge(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		ft_memdel(lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}
