/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:53:34 by cblasphe          #+#    #+#             */
/*   Updated: 2019/10/13 21:14:04 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t len)
{
	char *dst;

	dst = ft_strnew(len);
	if (dst == NULL)
		return (NULL);
	dst = ft_strncpy(dst, src, len);
	return (dst);
}
