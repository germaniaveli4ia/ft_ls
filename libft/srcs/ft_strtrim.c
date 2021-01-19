/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:49:32 by cblasphe          #+#    #+#             */
/*   Updated: 2019/09/14 18:35:26 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;

	if (s == NULL)
		return (NULL);
	start = 0;
	while (ft_isspace(s[start]))
		start++;
	if (s[start] == '\0')
		return (ft_strnew(0));
	end = ft_strlen(s) - 1;
	while (ft_isspace(s[end]))
		end--;
	return (ft_strsub(s, start, end - start + 1));
}
