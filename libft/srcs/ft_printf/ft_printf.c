/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:51:45 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 18:58:25 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_ifnonflag(t_mods *mods, const char *format, int i)
{
	if (!format[i] || i < 0)
		return (i);
	if (mods->fl & F_FMT_MINUS)
		ft_push_buffer(mods, format[i++]);
	mods->ind = ft_normalize_width(mods, 1);
	if (!(mods->fl & F_FMT_MINUS))
		ft_push_buffer(mods, format[i++]);
	return (i);
}

void	ft_flush(t_mods *mods)
{
	mods->fl = 0;
	mods->wid = 0;
	mods->prec = -1;
	mods->len = 0;
	mods->sgn = 0;
}

t_mods	*ft_init(void)
{
	t_mods	*mods;

	mods = ft_memalloc(sizeof(t_mods));
	mods->total_len = 0;
	ft_clear_buffer(mods);
	ft_flush(mods);
	return (mods);
}

int		ft_printf(const char *format, ...)
{
	size_t		i;
	t_mods		*mods;

	i = 0;
	mods = ft_init();
	va_start(mods->args, format);
	ft_parse_format(format, mods, i);
	ft_pop_buffer(mods);
	va_end(mods->args);
	free(mods);
	return (mods->total_len);
}
