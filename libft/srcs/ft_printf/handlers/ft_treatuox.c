/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatuox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:53:24 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 18:57:59 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_itoa_base_printf(uintmax_t n, int base, char type)
{
	char		*str;
	int			len;
	uintmax_t	tmp;

	len = 0;
	tmp = n;
	if (tmp == 0)
		return (ft_strdup("0"));
	while (tmp)
	{
		tmp /= base;
		++len;
	}
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	while (len)
	{
		str[--len] = (n % base < 10) ? n % base + '0' : n % base - 10 + type;
		n /= base;
	}
	return (str);
}

void		ft_treatuox(t_mods *mods, uintmax_t val, int base, char type)
{
	char	*str_val;
	size_t	len;

	str_val = NULL;
	mods->fl &= ~F_SPACE;
	if (mods->fl & F_HASH)
	{
		mods->wid -= (base == 16) ? 2 : 1;
		mods->prec -= (type == 'o') ? 1 : 0;
	}
	str_val = ft_itoa_base_printf(val, base, ft_isupper(type) ? 'A' : 'a');
	len = ft_strlen(str_val);
	if ((size_t)mods->prec < len && val != 0)
		mods->prec = -1;
	if (mods->fl & F_FMT_MINUS)
		mods->ind = ft_prec_numb(mods, str_val, len, type);
	mods->ind = ft_normalize_width(mods,
						(mods->prec >= 0 ? (size_t)mods->prec : len));
	if (!(mods->fl & F_FMT_MINUS))
		mods->ind = ft_prec_numb(mods, str_val, len, type);
	free(str_val);
}

uintmax_t	ft_getuval(char type, int length, t_mods *mods)
{
	uintmax_t	val;

	val = 0;
	if (type == 'U')
		val = (unsigned long)va_arg(mods->args, unsigned long);
	else if (!length)
		val = (unsigned int)va_arg(mods->args, unsigned int);
	else if (length == 2 * H)
		val = (unsigned char)va_arg(mods->args, int);
	else if (length == H)
		val = (unsigned short int)va_arg(mods->args, int);
	else if (length == L)
		val = (unsigned long int)va_arg(mods->args, unsigned long int);
	else if (length == 2 * L)
		val = (uintmax_t)va_arg(mods->args, unsigned long long int);
	else if (length == J)
		val = (uintmax_t)va_arg(mods->args, uintmax_t);
	else if (length == Z)
		val = (size_t)va_arg(mods->args, size_t);
	else
		val = (unsigned long)va_arg(mods->args, unsigned long);
	return (val);
}

void		ft_ifunsigned(t_mods *mods, char type)
{
	uintmax_t	val;
	int			base;

	val = 0;
	val = ft_getuval(mods->type, mods->len, mods);
	if (type == 'o')
		base = 8;
	else if (type == 'u' || type == 'U')
		base = 10;
	else
		base = 16;
	if (!val && mods->prec < 0 && mods->fl & F_DOT)
		mods->prec = 0;
	if ((val && mods->prec < 0 && mods->fl & F_DOT)
			|| (!val && !mods->prec && (mods->fl & F_HASH) && base == 8))
		mods->prec = 1;
	if (!val || base == 10)
		mods->fl &= ~F_HASH;
	mods->fl = (mods->prec >= 0) ? mods->fl & ~F_ZERO : mods->fl;
	ft_treatuox(mods, val, base, type);
}
