/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifications.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:52:04 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 19:02:44 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flags(char cur_char, t_mods *mods)
{
	if (cur_char == '-')
		mods->fl |= F_FMT_MINUS;
	else if (cur_char == '+')
		mods->fl |= F_PLUS;
	else if (cur_char == ' ')
		mods->fl |= F_SPACE;
	else if (cur_char == '#')
		mods->fl |= F_HASH;
	else if (cur_char == '0' && !(mods->fl & F_DOT) && !mods->wid)
		mods->fl |= F_ZERO;
	else
		return (0);
	if (mods->fl & F_FMT_MINUS)
		mods->fl &= ~F_ZERO;
	if (mods->fl & F_PLUS)
		mods->fl &= ~F_SPACE;
	return (1);
}

int		ft_width(char cur_char, t_mods *mods)
{
	if (mods->fl & F_DOT)
		return (0);
	if (cur_char != '*' && !ft_isdigit(cur_char))
		return (0);
	if (cur_char == '*')
	{
		mods->fl |= F_STAR;
		mods->wid = va_arg(mods->args, int);
		if (mods->wid < 0)
		{
			mods->wid *= -1;
			mods->fl |= F_FMT_MINUS;
			mods->fl &= ~F_ZERO;
		}
	}
	if (ft_isdigit(cur_char))
	{
		if (mods->fl & F_STAR)
			mods->wid = 0;
		mods->fl &= ~F_STAR;
		mods->wid = mods->wid * 10 + (cur_char - '0');
	}
	return (1);
}

int		ft_precision(char cur_char, t_mods *mods)
{
	if (cur_char == '.')
	{
		mods->fl = (mods->fl & ~F_STAR) | F_DOT;
		mods->prec = -1;
	}
	else if (cur_char == '*')
	{
		mods->fl |= F_STAR;
		mods->prec = va_arg(mods->args, int);
		if (mods->prec <= -1)
		{
			mods->prec = -1;
			mods->fl &= ~F_DOT;
		}
	}
	else if (ft_isdigit(cur_char)
			&& (mods->fl & F_DOT) && !(mods->fl & F_STAR))
	{
		if (mods->prec < 0)
			mods->prec = 0;
		mods->prec = mods->prec * 10 + (cur_char - '0');
	}
	else
		return (0);
	return (1);
}
