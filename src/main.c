/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 00:26:27 by alkapolly         #+#    #+#             */
/*   Updated: 2020/08/13 02:07:59 by alkapolly        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	t_flags	*flags;
	t_size	*size;

	flags = NULL;
	size = NULL;
	if (!(flags = init_flags()))
		ft_error(0, 0, 0);
	if (!(size = init_size()))
		ft_error(0, flags, 0);
	if (argc)
		ft_parse_and_process_args(++argv, flags, size);
	free(flags);
	free(size);
	return (0);
}
