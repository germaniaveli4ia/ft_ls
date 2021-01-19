/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 21:53:39 by cblasphe          #+#    #+#             */
/*   Updated: 2019/09/25 22:48:20 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *need, size_t len)
{
	size_t	i;
	size_t	k;
	size_t	hay_len;
	size_t	nee_len;

	if (*need == '\0' || haystack == need)
		return ((char *)haystack);
	i = 0;
	nee_len = ft_strlen(need);
	hay_len = ft_strlen(haystack);
	while (i < len && i < hay_len)
	{
		k = 0;
		while (k < nee_len && i + k < len && haystack[i + k] == need[k])
			k++;
		if (need[k] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
