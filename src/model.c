/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:04:29 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/10 17:37:07 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <fcntl.h>
#include <unistd.h>

int			init_file(t_env *env)
{
	int		fd;

	fd = open(env->file_name, O_RDONLY);
	init_stream(&env->stream, fd);
	env->stream.fd = fd;
	return (header);
}

int			build_data(t_env *env)
{
	env->activated[parser] = OFF;
	verification(env);
	play_sound(env, "audio.mp3");
	return (file);
}

int			save_file(t_env *env)
{
	int		fd;

	fd = open("saved_map.doom", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == ERROR)
		return (ERROR);
	init_stream(&env->stream_out, fd);
	save_content(env);
	flush_out(&env->stream_out);
	close(fd);
	return (SUCCESS);
}
