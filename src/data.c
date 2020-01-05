/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 23:14:42 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/10 17:21:59 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			fill_object(t_env *env)
{
	t_stream	*s;
	int			floor;
	int			ceiling;
	int			texture;

	s = &(env->stream);
	env->object[env->card[e_object]].pos.x = get_val(s, -MAX_DIST, MAX_DIST);
	env->object[env->card[e_object]].pos.y = get_val(s, -MAX_DIST, MAX_DIST);
	floor = get_val(s, MIN_ALTITUDE, MAX_ALTITUDE);
	ceiling = get_val(s, MIN_ALTITUDE, MAX_ALTITUDE);
	texture = ft_get_nb(s);
	env->object[env->card[e_object]].a.floor = floor;
	env->object[env->card[e_object]].b.floor = floor;
	env->object[env->card[e_object]].a.ceiling = ceiling;
	env->object[env->card[e_object]].b.ceiling = ceiling;
	env->object[env->card[e_object]].a.texture = texture;
	env->object[env->card[e_object]].b.texture = texture;
	env->object[env->card[e_object]].pickable = get_val(s, 0, 3);
	env->object[env->card[e_object]].animated = get_val(s, 0, 2);
	env->object[env->card[e_object]].reaction = get_val(s, 0, NB_REACTIONS);
	env->object[env->card[e_object]].nl = get_val(s, 0, 2);
	env->object[env->card[e_object]].effect = get_val(s, -999, 32);
	env->object[env->card[e_object]].color = 0xFFFFFF;
	env->object[env->card[e_object]].prio = 0;
	env->card[e_object]++;
}

void			fill_wall(t_env *env, int current_sector)
{
	t_stream	*s;
	int			current_wall;

	s = &(env->stream);
	current_wall = env->current_wall;
	env->wall[current_wall].pos.x = get_val(s, -MAX_DIST, MAX_DIST);
	env->wall[current_wall].pos.y = get_val(s, -MAX_DIST, MAX_DIST);
	env->wall[current_wall].next_sector = get_val(s, -1, NB_SECTORS);
	env->wall[current_wall].texture = get_val(s, -1, NB_TEXTURES);
	env->wall[current_wall].sector = current_sector;
	env->wall[current_wall].floor = env->sector[current_sector].floor;
	env->wall[current_wall].ceiling = env->sector[current_sector].ceiling;
}

void			fill_sector(t_env *env, int current_sector)
{
	t_stream	*s;
	int			left_walls;

	s = &(env->stream);
	left_walls = NB_WALLS - env->card[e_wall];
	env->sector[current_sector].num_walls = get_val(s, 0, left_walls + 1);
	if (env->sector[current_sector].num_walls >= max_val(e_wall))
		env->sector[current_sector].num_walls = NB_WALLS;
	env->sector[current_sector].floor = get_val(s, MIN_ALTITUDE, MAX_ALTITUDE);
	env->sector[current_sector].ceiling =
	get_val(s, MIN_ALTITUDE, MAX_ALTITUDE);
	env->sector[current_sector].tex_f = get_val(s, -1, NB_TEXTURES);
	env->sector[current_sector].tex_c = get_val(s, -1, NB_TEXTURES);
	env->sector[current_sector].start_wall = env->card[e_wall];
	env->sector[current_sector].luminosity = get_val(s, -1000, 1001) / 100.0;
	if (env->sector[current_sector].luminosity < 0)
	{
		env->sector[current_sector].luminosity =
		fabs(env->sector[current_sector].luminosity);
		env->sector[current_sector].light = 1;
	}
	else
		env->sector[current_sector].light = 0;
	env->sector[current_sector].animated = get_val(s, 0, 2);
	env->sector[current_sector].reaction = get_val(s, 0, NB_REACTIONS);
}

int				fill_vm(t_env *env, int type_actor, int i)
{
	t_stream	*s;

	s = &(env->stream);
	env->action[type_actor].mini_vm[i++] = extract_param(s);
	env->action[type_actor].mini_vm[i++] = extract_param(s);
	if (ft_getchar(&env->stream) == LABEL_REG)
		env->action[type_actor].mini_vm[i++] = extract_param(s);
	else
	{
		env->action[type_actor].mini_vm[i++] = ft_get_nb(s);
		env->action[type_actor].mini_vm[i] = TRUE;
	}
	return (++i);
}
