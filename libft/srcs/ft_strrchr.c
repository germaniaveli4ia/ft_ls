/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 19:09:33 by cblasphe          #+#    #+#             */
/*   Updated: 2019/09/14 19:19:36 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *ptr;

	ptr = (char *)s;
	while (*ptr)
		ptr++;
	while (ptr != s && *ptr != (char)c)
		ptr--;
	if (*ptr == (char)c)
		return (ptr);
	return (NULL);
}
