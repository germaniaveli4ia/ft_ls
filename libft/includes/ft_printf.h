/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 22:57:30 by cblasphe          #+#    #+#             */
/*   Updated: 2020/08/13 18:58:25 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# define ALLSIMBOLS "cspdiouUxXfFn#-+ .*0123456789hLljz"
# define TYPES		"cspdiouUxXfFn"
# define SPECS		"#-+ .*0123456789hLljz"
# define BUF_SIZE 	64

# define H			1
# define L			10
# define LD			100
# define J			1000
# define Z			10000

# define F_ZERO		1
# define F_HASH		2
# define F_SPACE	4
# define F_DOT		8
# define F_STAR		16
# define F_PLUS		32
# define F_FMT_MINUS	64

typedef struct		s_mods
{
	va_list			args;
	char			*check;
	size_t			pos;
	char			buf[BUF_SIZE];
	int				fl;
	char			type;
	int				ind;
	int				wid;
	int				prec;
	int				len;
	size_t			total_len;
	int				sgn;
}					t_mods;

int					ft_printf(const char *formst, ...);
int					ft_parse_format(const char *format, t_mods *mods,
															size_t i);
void				ft_ifchar(t_mods *mods);
void				ft_ifstr(t_mods *mods);
void				ft_ifint(t_mods *mods);
void				ft_iffloat(t_mods *mods);
void				ft_ifptr(t_mods *mods);
void				ft_ifn(t_mods *mods);
void				ft_ifunsigned(t_mods *mods, char type);

int					ft_flags(char cur_char, t_mods *mods);
int					ft_width(char cur_char, t_mods *mods);
int					ft_precision(char cur_char, t_mods *mods);
int					ft_normalize_width(t_mods *mods, size_t len);
char				*ft_itoa_base_printf(uintmax_t n, int base, char type);
int					ft_prec_numb(t_mods *mods, char *str, size_t len,
																char utype);
int					ft_prec_float(t_mods *mods, char *str);
void				ft_push_buffer(t_mods *mods, char c);
void				ft_push_str_to_buffer(t_mods *mods, char *str);
void				ft_pop_buffer(t_mods *mods);
void				ft_clear_buffer(t_mods *mods);
char				*ft_fitoa(uintmax_t dec, int dec_len, int16_t *fract,
															t_mods *mods);
char				*ft_getstr_val(t_mods *mods, long double val,
													char *str_val, int i);
int					ft_getdec_len(uintmax_t tmp, long double val);
int16_t				*ft_get_fract_digs(t_mods *mods, long double val);

void				ft_flush(t_mods *mods);
int					ft_ifnonflag(t_mods *mods, const char *format, int i);
#endif
