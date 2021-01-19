/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:57:52 by cblasphe          #+#    #+#             */
/*   Updated: 2019/09/26 17:03:25 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *node;

	node = (t_list*)ft_memalloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->next = NULL;
	if (!content)
	{
		node->content = NULL;
		node->content_size = 0;
	}
	else
	{
		node->content = ft_memdup(content, content_size);
		if (!node->content)
		{
			free(node);
			return (NULL);
		}
		node->content_size = content_size;
	}
	return (node);
}
