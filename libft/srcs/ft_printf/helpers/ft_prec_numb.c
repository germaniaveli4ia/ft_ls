/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prec_numb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:53:54 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 18:58:25 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_get_limit(t_mods *mods, size_t len)
{
	if (mods->type == 'f')
		return (len);
	return ((mods->prec > 0) ? (size_t)mods->prec : len);
}

void	ft_push_sign(t_mods *mods)
{
	if (mods->sgn == 1 && mods->fl & F_PLUS)
		ft_push_buffer(mods, '+');
	else if (mods->sgn < 0)
		ft_push_buffer(mods, '-');
	else if (mods->fl & F_SPACE)
		ft_push_buffer(mods, ' ');
}

int		ft_prec_numb(t_mods *mods, char *str, size_t len, char utype)
{
	int		count;
	size_t	limit;

	count = 0;
	limit = ft_get_limit(mods, len);
	ft_push_sign(mods);
	if ((mods->fl & F_HASH) && utype)
		ft_push_buffer(mods, '0');
	if ((mods->fl & F_HASH) && (utype == 'x' || utype == 'X'))
		ft_push_buffer(mods, utype);
	if (mods->prec > 0 && ft_strchr("dipuoxX", mods->type))
		while (len++ < limit)
			ft_push_buffer(mods, '0');
	if (mods->type == 'p')
		limit = len;
	while (mods->prec && str[count] && (size_t)count < limit)
		ft_push_buffer(mods, str[count++]);
	return (mods->ind);
}

int		ft_prec_float(t_mods *mods, char *str)
{
	ft_push_sign(mods);
	ft_push_str_to_buffer(mods, str);
	return (mods->ind);
}
