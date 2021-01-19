/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 21:57:43 by cblasphe          #+#    #+#             */
/*   Updated: 2019/10/09 22:49:59 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(void const *src, size_t size)
{
	unsigned char	*dst;

	if (src == NULL)
		return (NULL);
	dst = (unsigned char*)ft_memalloc(size);
	if (dst == NULL)
		return (NULL);
	return (ft_memcpy(dst, src, size));
}
