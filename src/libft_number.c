/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 19:23:12 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/07 03:09:26 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	ft_write_nb(int nb, t_stream *out)
{
	if (nb >= 10)
		ft_write_nb(nb / 10, out);
	ft_putc(out, nb % 10 + '0');
}

void		write_value(int nb, t_stream *out)
{
	if (nb < 0)
	{
		nb *= -1;
		ft_putc(out, '-');
	}
	ft_write_nb(nb, out);
	ft_putc(out, ' ');
}

int			ft_get_nb(t_stream *s)
{
	int		nb;
	int		c;
	int		sign;

	nb = 0;
	sign = 0;
	skip_space(s);
	if (ft_getchar(s) == '-' && ft_getc(s))
		sign = 1;
	while ((c = ft_getchar(s)) && c >= '0' && c <= '9' && ft_getc(s) >= 0)
		nb = nb * 10 + c - '0';
	if (sign)
		nb *= -1;
	skip_space(s);
	return (nb);
}
