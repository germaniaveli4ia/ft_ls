/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatcsp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:52:27 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 19:05:30 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_normalize_width(t_mods *mods, size_t len)
{
	if ((mods->fl & F_ZERO) && (mods->sgn < 0 || mods->sgn == 1
														|| mods->fl & F_HASH))
	{
		if (mods->sgn == 1 && mods->fl & F_SPACE)
			ft_push_buffer(mods, ' ');
		else if (mods->sgn == 1 || mods->sgn < 0)
			ft_push_buffer(mods, (mods->sgn < 0) ? '-' : '+');
		else if (mods->fl & F_HASH)
		{
			ft_push_buffer(mods, '0');
			if (mods->type == 'x' || mods->type == 'X')
				ft_push_buffer(mods, mods->type);
			mods->fl &= ~F_HASH;
		}
		mods->sgn = 2;
		mods->fl &= ~F_SPACE;
	}
	while (mods->wid - (int)len > 0)
	{
		ft_push_buffer(mods, (mods->fl & F_ZERO) ? '0' : ' ');
		mods->wid--;
	}
	return (mods->ind);
}

int		ft_putstrwithprec(t_mods *mods, int precision, char *str, size_t len)
{
	size_t count;
	size_t limit;

	count = 0;
	limit = (precision >= 0) ? (size_t)precision : len;
	while (count < limit)
		ft_push_buffer(mods, str[count++]);
	return (mods->ind);
}

void	ft_ifchar(t_mods *mods)
{
	unsigned char c;

	c = (unsigned char)va_arg(mods->args, int);
	if (mods->fl & F_FMT_MINUS)
		ft_push_buffer(mods, c);
	mods->ind = ft_normalize_width(mods, 1);
	if (!(mods->fl & F_FMT_MINUS))
		ft_push_buffer(mods, c);
}

void	ft_ifstr(t_mods *mods)
{
	char	*str;
	size_t	len;
	size_t	precision;

	mods->fl &= ~F_PLUS;
	mods->fl &= ~F_SPACE;
	if (!(str = (char *)va_arg(mods->args, char *)))
		str = "(null)";
	len = ft_strlen(str);
	if ((size_t)mods->prec > len)
		mods->prec = -1;
	if (mods->fl & F_FMT_MINUS)
		mods->ind = ft_putstrwithprec(mods, mods->prec, str, len);
	precision = (mods->prec >= 0) ? (size_t)mods->prec : len;
	mods->ind = ft_normalize_width(mods, precision);
	if (!(mods->fl & F_FMT_MINUS))
		mods->ind = ft_putstrwithprec(mods, mods->prec, str, len);
}

void	ft_ifptr(t_mods *mods)
{
	uintmax_t	p;
	char		*str_pval;
	size_t		len;

	mods->fl |= F_HASH;
	p = (uintmax_t)va_arg(mods->args, void *);
	str_pval = ft_itoa_base_printf(p, 16, 'a');
	len = ft_strlen(str_pval);
	if (!mods->prec && !p)
	{
		mods->ind = ft_prec_numb(mods, str_pval, len - 1, 'x');
		return ;
	}
	if (mods->fl & F_FMT_MINUS)
		mods->ind = ft_prec_numb(mods, str_pval, len, 'x');
	mods->ind = ft_normalize_width(mods, len + 2);
	if (mods->wid < mods->prec)
		mods->wid = mods->prec;
	if (!(mods->fl & F_FMT_MINUS))
		mods->ind = ft_prec_numb(mods, str_pval, len, 'x');
	if (str_pval)
		ft_strdel(&str_pval);
}
