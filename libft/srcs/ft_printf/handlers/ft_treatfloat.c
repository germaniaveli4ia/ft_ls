/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatfloat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:52:43 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 19:06:09 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_float2(t_mods *mods, long double val, char *str, int fract_len)
{
	size_t	ful_len;
	size_t	i;

	i = 0;
	ful_len = ft_strlen(str);
	if (mods->type == 'F')
		while (i < ful_len)
			ft_toupper(str[i++]);
	if (mods->prec < fract_len && val != 0)
		mods->prec = -1;
	if ((mods->sgn != 0 || mods->fl & F_SPACE) && mods->wid)
		mods->wid -= 1;
	if (val != val)
	{
		mods->fl &= ~F_ZERO & ~F_SPACE;
		mods->sgn = 0;
	}
	if (mods->fl & F_FMT_MINUS)
		mods->ind = ft_prec_float(mods, str);
	mods->ind = ft_normalize_width(mods, ful_len);
	mods->sgn = (mods->sgn == 2) ? 0 : mods->sgn;
	if (!(mods->fl & F_FMT_MINUS))
		mods->ind = ft_prec_float(mods, str);
	if (str)
		ft_strdel(&str);
}

int16_t		*ft_get_fract_digs(t_mods *mods, long double val)
{
	short int		*digs;
	int				i;

	if (!(digs = (short int*)ft_memalloc((mods->prec + 1) * sizeof(short int))))
		return (NULL);
	i = 0;
	val -= (uintmax_t)val;
	while (i <= mods->prec)
	{
		val *= 10;
		digs[i] = (int)val;
		val -= (int)val;
		i++;
	}
	return (digs);
}

int			ft_getdec_len(uintmax_t tmp, long double val)
{
	int				dec_len;

	dec_len = 0;
	while (tmp)
	{
		tmp = tmp / 10;
		dec_len++;
	}
	dec_len = ((long long)val == 0) ? 1 : dec_len;
	return (dec_len);
}

void		ft_treatfloat1(t_mods *mods, long double val)
{
	char			*str_val;
	int				i;

	str_val = NULL;
	i = 0;
	if (val == 1.0 / 0.0)
	{
		mods->fl &= ~F_ZERO;
		str_val = ft_strdup("inf");
	}
	else if (val != val)
		str_val = ft_strdup("nan");
	else
		str_val = ft_getstr_val(mods, val, str_val, i);
	ft_float2(mods, val, str_val, mods->prec);
}

void		ft_iffloat(t_mods *mods)
{
	long double	val;

	val = 0.0;
	if (mods->len == LD)
		val = va_arg(mods->args, long double);
	else
		val = (long double)va_arg(mods->args, double);
	if (mods->prec < 0)
		mods->prec = 6;
	if (val < 0)
	{
		mods->sgn = -1;
		val *= -1;
		mods->fl &= ~F_SPACE;
	}
	else if (val >= 0 && (mods->fl & F_PLUS || mods->fl & F_SPACE))
		mods->sgn = 1;
	ft_treatfloat1(mods, val);
}
