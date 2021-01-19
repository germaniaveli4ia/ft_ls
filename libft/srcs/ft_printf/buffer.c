/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:51:07 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 18:57:08 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_clear_buffer(t_mods *mods)
{
	mods->ind = 0;
	mods->pos = 0;
}

void	ft_pop_buffer(t_mods *mods)
{
	write(1, mods->buf, mods->ind);
	ft_clear_buffer(mods);
}

int		ft_buffer_is_full(t_mods *mods)
{
	return (mods->ind == BUF_SIZE);
}

void	ft_push_buffer(t_mods *mods, char c)
{
	if (ft_buffer_is_full(mods))
		ft_pop_buffer(mods);
	mods->total_len++;
	mods->buf[mods->ind++] = c;
}

void	ft_push_str_to_buffer(t_mods *mods, char *str)
{
	while (*str)
	{
		ft_push_buffer(mods, *str);
		str++;
	}
}
