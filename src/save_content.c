/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:50:00 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 23:28:30 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		save_sectors(t_env *env)
{
	int			i;

	i = 0;
	ft_putstr(&env->stream_out, "[--[ MAP ]--]\n");
	ft_putstr(&env->stream_out, "== sectors == ");
	write_value(env->card[e_sector], &env->stream_out);
	ft_putc(&env->stream_out, '\n');
	while (i < env->card[e_sector])
	{
		write_value(env->sector[i].num_walls, &env->stream_out);
		write_value(env->sector[i].floor, &env->stream_out);
		write_value(env->sector[i].ceiling, &env->stream_out);
		write_value(env->sector[i].tex_f, &env->stream_out);
		write_value(env->sector[i].tex_c, &env->stream_out);
		write_value(env->sector[i].luminosity * 100.0
			* (env->sector[i].light == 1 ? -1 : 1), &env->stream_out);
		write_value(env->sector[i].animated, &env->stream_out);
		write_value(env->sector[i].reaction, &env->stream_out);
		ft_putc(&env->stream_out, '\n');
		i++;
	}
	ft_putc(&env->stream_out, '\n');
}

static void		save_walls(t_env *env)
{
	int			i;

	i = 0;
	while (i < env->card[e_wall])
	{
		write_value(env->wall[i].pos.x, &env->stream_out);
		write_value(env->wall[i].pos.y, &env->stream_out);
		write_value(env->wall[i].next_sector, &env->stream_out);
		write_value(env->wall[i].texture, &env->stream_out);
		ft_putc(&env->stream_out, '\n');
		i++;
	}
}

static void		save_textures(t_env *env)
{
	int			i;
	int			j;

	i = 0;
	ft_putstr(&env->stream_out, "[--[ TEXTURE ]--]\n");
	ft_putstr(&env->stream_out, "== pictures == ");
	write_value(env->card[e_texture], &env->stream_out);
	ft_putc(&env->stream_out, '\n');
	while (i < env->card[e_texture])
	{
		j = 0;
		write_value(env->texture[i].w, &env->stream_out);
		write_value(env->texture[i].h, &env->stream_out);
		write_value(env->texture[i].size, &env->stream_out);
		ft_putc(&env->stream_out, '\n');
		while (j < env->texture[i].w * env->texture[i].h * 4)
			if (j % 4 != 3)
				write_value(env->texture[i].picture[j++], &env->stream_out);
			else
				j++;
		ft_putc(&env->stream_out, '\n');
		i++;
	}
}

static void		save_objects(t_env *env)
{
	int			i;

	i = 0;
	ft_putstr(&env->stream_out, "[--[ OBJECT ]--]\n");
	ft_putstr(&env->stream_out, "== object == ");
	write_value(env->card[e_object], &env->stream_out);
	ft_putc(&env->stream_out, '\n');
	while (i < env->card[e_object])
	{
		write_value(env->object[i].pos.x, &env->stream_out);
		write_value(env->object[i].pos.y, &env->stream_out);
		write_value(env->object[i].a.floor, &env->stream_out);
		write_value(env->object[i].a.ceiling, &env->stream_out);
		write_value(env->object[i].a.texture, &env->stream_out);
		write_value(env->object[i].pickable, &env->stream_out);
		write_value(env->object[i].animated, &env->stream_out);
		write_value(env->object[i].reaction, &env->stream_out);
		write_value(env->object[i].nl, &env->stream_out);
		write_value(env->object[i].effect, &env->stream_out);
		ft_putc(&env->stream_out, '\n');
		i++;
	}
}

void			save_content(t_env *env)
{
	save_player(env);
	save_sectors(env);
	save_walls(env);
	save_textures(env);
	save_objects(env);
	save_character(env);
	save_sentences(env);
	save_font(env);
}
