/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:52:54 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 18:58:25 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_treatint(t_mods *mods, uintmax_t val)
{
	char	*str_val;
	size_t	len;

	str_val = ft_itoa_base_printf(val, 10, 'A');
	len = ft_strlen(str_val);
	if ((size_t)mods->prec < len && val != 0)
		mods->prec = -1;
	if ((mods->sgn != 0 || mods->fl & F_SPACE) && mods->wid)
		mods->wid -= 1;
	if (mods->fl & F_FMT_MINUS)
		mods->ind = ft_prec_numb(mods, str_val, len, mods->sgn);
	mods->ind = ft_normalize_width(mods,
						(mods->prec >= 0 ? (size_t)mods->prec : len));
	mods->sgn = (mods->sgn == 2) ? 0 : mods->sgn;
	if (!(mods->fl & F_FMT_MINUS))
		mods->ind = ft_prec_numb(mods, str_val, len, mods->sgn);
	if (str_val)
		ft_strdel(&str_val);
}

void	ft_check_sign(t_mods *mods, long long *val)
{
	if (*val < 0)
	{
		mods->sgn = -1;
		mods->fl &= ~F_SPACE;
		*val *= -1;
	}
	else if (*val >= 0 && (mods->fl & F_PLUS || mods->fl & F_SPACE))
		mods->sgn = 1;
}

void	ft_ifint(t_mods *mods)
{
	long long int	val;

	val = 0;
	mods->fl &= ~F_HASH;
	if (!mods->len)
		val = (int)va_arg(mods->args, int);
	else if (mods->len == 2 * H)
		val = (signed char)va_arg(mods->args, int);
	else if (mods->len == H)
		val = (short int)va_arg(mods->args, int);
	else if (mods->len == L)
		val = (long int)va_arg(mods->args, long int);
	else if (mods->len == 2 * L)
		val = (long long int)va_arg(mods->args, long long int);
	else if (mods->len == J)
		val = (intmax_t)va_arg(mods->args, intmax_t);
	else if (mods->len == Z)
		val = (ssize_t)va_arg(mods->args, ssize_t);
	else
		val = (unsigned long)va_arg(mods->args, unsigned long);
	mods->fl = (mods->prec >= 0) ? mods->fl & ~F_ZERO : mods->fl;
	ft_check_sign(mods, &val);
	ft_treatint(mods, (uintmax_t)val);
}
