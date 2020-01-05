/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 03:03:32 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/07 03:09:39 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <unistd.h>

void		ft_putc(t_stream *out, char c)
{
	out->buff[out->i++] = c;
	if (out->i >= BUFFER_SIZE)
		flush_out(out);
}

void		ft_putstr(t_stream *out, char *s)
{
	while (*s)
		ft_putc(out, *s++);
}

void		flush_out(t_stream *out)
{
	int	ret;

	ret = write(out->fd, out->buff, out->i);
	out->i = 0;
}
