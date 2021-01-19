/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 21:27:18 by cblasphe          #+#    #+#             */
/*   Updated: 2019/09/25 20:56:54 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;
	size_t k;
	size_t hay_len;
	size_t nee_len;

	if (*needle == '\0' || haystack == needle)
		return ((char *)haystack);
	i = 0;
	nee_len = ft_strlen(needle);
	hay_len = ft_strlen(haystack);
	if (hay_len < nee_len)
		return (NULL);
	while (i < hay_len - nee_len + 1)
	{
		k = 0;
		while (k < nee_len && haystack[i + k] == needle[k])
			k++;
		if (needle[k] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
