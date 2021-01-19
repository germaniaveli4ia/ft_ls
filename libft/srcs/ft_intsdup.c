/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <cblasphe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:06:33 by cblasphe          #+#    #+#             */
/*   Updated: 2020/01/11 20:13:02 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_intsdup(int *arr, size_t size)
{
	int		*duplicate;
	size_t	i;

	i = 0;
	duplicate = (int *)malloc(sizeof(int) * size);
	if (!duplicate)
		return (NULL);
	while (i < size)
	{
		duplicate[i] = arr[i];
		i++;
	}
	return (duplicate);
}
