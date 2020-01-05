/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_sound.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 02:03:13 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/07 03:27:57 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <fcntl.h>

int				extract_sound(t_env *env)
{
	int			nb;
	t_stream	*s;
	int			fd;

	fd = open("audio.mp3", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == ERROR)
		return (ERROR);
	s = &(env->stream);
	init_stream(&env->stream_out, fd);
	nb = ft_get_nb(&env->stream);
	while (nb--)
		ft_putc(&env->stream_out, ft_getc(&env->stream));
	flush_out(&env->stream_out);
	return (header);
}
