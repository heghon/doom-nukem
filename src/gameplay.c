/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 20:21:10 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 20:51:48 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "../include/SDL.h"
#include <math.h>

static void	fps_calc(t_env *e)
{
	e->fps_count.deltaclock = SDL_GetTicks() - e->fps_count.startclock;
	e->fps_count.startclock = SDL_GetTicks();
	if (e->fps_count.deltaclock != 0)
		e->fps_count.current_fps = 1000 / e->fps_count.deltaclock;
}

static void	pk_movements(t_env *e, float mult, float div)
{
	e->p.mov.x = 0;
	e->p.mov.y = 0;
	e->p.mov.x += (float)SPEED * e->p.dir.x * e->keys[SDLK_w % 42]
						* (float)(e->fps_count.deltaclock / 1000.0) * mult;
	e->p.mov.y += (float)SPEED * e->p.dir.y * e->keys[SDLK_w % 42]
						* (float)(e->fps_count.deltaclock / 1000.0) * mult;
	e->p.mov.x -= (float)SPEED * e->p.dir.x * e->keys[SDLK_s % 42]
						* (float)(e->fps_count.deltaclock / 1000.0) * div;
	e->p.mov.y -= (float)SPEED * e->p.dir.y * e->keys[SDLK_s % 42]
						* (float)(e->fps_count.deltaclock / 1000.0) * div;
	e->p.mov.x += (float)SPEED * e->p.dir.y * e->keys[SDLK_a % 42]
						* (float)(e->fps_count.deltaclock / 1000.0) * div;
	e->p.mov.y -= (float)SPEED * e->p.dir.x * e->keys[SDLK_a % 42]
						* (float)(e->fps_count.deltaclock / 1000.0) * div;
	e->p.mov.x -= (float)SPEED * e->p.dir.y * e->keys[SDLK_d % 42]
						* (float)(e->fps_count.deltaclock / 1000.0) * div;
	e->p.mov.y += (float)SPEED * e->p.dir.x * e->keys[SDLK_d % 42]
						* (float)(e->fps_count.deltaclock / 1000.0) * div;
	if (e->keys[SDLK_LSHIFT % 42])
	{
		e->p.mov.x *= 2.0;
		e->p.mov.y *= 2.0;
	}
}

static void	calcul_rot(t_env *env, double sens)
{
	float	tmp;

	tmp = env->p.dir.x;
	env->p.dir.x = (env->p.dir.x * cos(sens * SPEED_ANGLE)
					- env->p.dir.y * sin(sens * SPEED_ANGLE));
	env->p.dir.y = (tmp * sin(sens * SPEED_ANGLE)
					+ env->p.dir.y * cos(sens * SPEED_ANGLE));
	env->p.left.x = (env->p.dir.x * cos(-ANGLE_VISION)
					- env->p.dir.y * sin(-ANGLE_VISION));
	env->p.left.y = (env->p.dir.x * sin(-ANGLE_VISION)
					+ env->p.dir.y * cos(-ANGLE_VISION));
	env->p.right.x = (env->p.dir.x * cos(ANGLE_VISION)
					- env->p.dir.y * sin(ANGLE_VISION));
	env->p.right.y = (env->p.dir.x * sin(ANGLE_VISION)
					+ env->p.dir.y * cos(ANGLE_VISION));
}

static void	update_fov(t_env *e)
{
	calcul_rot(e, -1.0 * e->keys[SDLK_LEFT % 42]);
	calcul_rot(e, 1.0 * e->keys[SDLK_RIGHT % 42]);
}

void		move_player(t_env *e)
{
	int		ret;
	t_float	tmp[2];

	fps_calc(e);
	e->p.state == crouch ? pk_movements(e, 20.0, 20.0)
						: pk_movements(e, 200.0, 200.0);
	e->col_recursive = 0;
	ret = collision_check(e);
	tmp[0] = e->p.pos;
	tmp[1] = e->p.dir;
	update_position(e);
	if (ret == 2)
	{
		new_cord(e);
		update_position(e);
		e->rend.first_portal = e->rend.all;
	}
	if (in_which_sector(e) == -1)
	{
		e->p.pos = tmp[0];
		e->p.dir = tmp[1];
	}
	look_around(e);
	update_fov(e);
	bound_box_p(e);
}
