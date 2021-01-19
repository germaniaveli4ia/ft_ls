/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:53:39 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 18:56:52 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_fitoa(uintmax_t dec, int dec_len, int16_t *fract, t_mods *mods)
{
	char		*str;
	int			ful_len;
	int			prec;

	prec = mods->prec;
	ful_len = dec_len + prec + ((prec) ? 1 : 0);
	str = ft_strnew(ful_len);
	if (str == NULL)
		return (NULL);
	while (prec--)
	{
		ful_len--;
		str[ful_len] = fract[prec] % 10 + '0';
	}
	if (mods->prec > 0 || mods->fl & F_HASH)
		str[(!mods->prec) ? ful_len : --ful_len] = '.';
	while (dec_len)
	{
		ful_len--;
		str[ful_len] = dec % 10 + '0';
		dec /= 10;
		dec_len--;
	}
	return (str);
}

void		ft_roundup(t_mods *mods, int i, int16_t *digs)
{
	int	max;

	max = i;
	while (i > 0)
	{
		if (mods->prec && ((digs[i] >= 5 && i == max) || (digs[i] == 10)))
		{
			digs[i - 1]++;
			digs[i] %= 10;
		}
		i--;
	}
}

char		*ft_getstr_val(t_mods *mods, long double val, char *str_val, int i)
{
	uintmax_t		tmp;
	int				dec_len;
	int16_t			*digs;

	dec_len = 0;
	tmp = (uintmax_t)val;
	dec_len = ft_getdec_len(tmp, val);
	digs = ft_get_fract_digs(mods, val);
	i = (mods->prec > 0) ? mods->prec : i;
	if (!mods->prec && digs[0] >= 5)
		val++;
	ft_roundup(mods, i, digs);
	if (digs[0] == 10 && (unsigned long long)val)
	{
		val++;
		digs[0] %= 10;
	}
	str_val = ft_fitoa((__uint128_t)val, dec_len, digs, mods);
	free(digs);
	return (str_val);
}
