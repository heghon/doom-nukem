/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmenant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 11:37:01 by bmenant           #+#    #+#             */
/*   Updated: 2019/11/09 16:50:27 by bmenant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <math.h>

static int	third_cases(t_env *e, float angle_diff, float mult)
{
	if ((e->p.dir.x <= 0 && e->p.dir.y <= 0 && e->keys[SDLK_w % 42])
		|| (e->p.dir.x >= 0 && e->p.dir.y >= 0 && e->keys[SDLK_s % 42])
		|| (e->p.dir.x >= 0 && e->p.dir.y <= 0 && e->keys[SDLK_a % 42])
		|| (e->p.dir.x <= 0 && e->p.dir.y >= 0 && e->keys[SDLK_d % 42]))
	{
		e->col.x = (e->col.sy < 0 && (57.2958 * angle_diff) > 90 ?
			fabs(e->col.sx) * mult : -fabs(e->col.sx) * mult);
		e->col.y = (e->col.sy < 0 && (57.2958 * angle_diff) < 90 ?
			fabs(e->col.sy) * mult : -fabs(e->col.sy) * mult);
		return (TRUE);
	}
	if ((e->p.dir.x <= 0 && e->p.dir.y >= 0 && e->keys[SDLK_w % 42])
		|| (e->p.dir.x >= 0 && e->p.dir.y <= 0 && e->keys[SDLK_s % 42])
		|| (e->p.dir.x <= 0 && e->p.dir.y <= 0 && e->keys[SDLK_a % 42])
		|| (e->p.dir.x >= 0 && e->p.dir.y >= 0 && e->keys[SDLK_d % 42]))
	{
		e->col.x = (e->col.sy > 0 && (57.2958 * angle_diff) > 90 ?
			fabs(e->col.sx) * mult : -fabs(e->col.sx) * mult);
		e->col.y = (e->col.sy > 0 && (57.2958 * angle_diff) < 90 ?
			-fabs(e->col.sy) * mult : fabs(e->col.sy) * mult);
		return (TRUE);
	}
	return (FALSE);
}

static int	second_cases(t_env *e, float angle_diff, float mult)
{
	if ((e->p.dir.x >= 0 && e->p.dir.y >= 0 && e->keys[SDLK_w % 42])
		|| (e->p.dir.x <= 0 && e->p.dir.y <= 0 && e->keys[SDLK_s % 42])
		|| (e->p.dir.x <= 0 && e->p.dir.y >= 0 && e->keys[SDLK_a % 42])
		|| (e->p.dir.x >= 0 && e->p.dir.y <= 0 && e->keys[SDLK_d % 42]))
	{
		e->col.x = (e->col.sy < 0 && (57.2958 * angle_diff) > 90 ?
			-fabs(e->col.sx) * mult : fabs(e->col.sx) * mult);
		e->col.y = (e->col.sy < 0 && (57.2958 * angle_diff) < 90 ?
			-fabs(e->col.sy) * mult : fabs(e->col.sy) * mult);
		return (TRUE);
	}
	if ((e->p.dir.x >= 0 && e->p.dir.y <= 0 && e->keys[SDLK_w % 42])
		|| (e->p.dir.x <= 0 && e->p.dir.y >= 0 && e->keys[SDLK_s % 42])
		|| (e->p.dir.x >= 0 && e->p.dir.y >= 0 && e->keys[SDLK_a % 42])
		|| (e->p.dir.x <= 0 && e->p.dir.y <= 0 && e->keys[SDLK_d % 42]))
	{
		e->col.x = (e->col.sy > 0 && (57.2958 * angle_diff) > 90 ?
			-fabs(e->col.sx) * mult : fabs(e->col.sx) * mult);
		e->col.y = (e->col.sy > 0 && (57.2958 * angle_diff) < 90 ?
			fabs(e->col.sy) * mult : -fabs(e->col.sy) * mult);
		return (TRUE);
	}
	return (FALSE);
}

static int	first_cases(t_env *e)
{
	if (isinf(e->col.a2))
	{
		e->col.x = 0;
		e->col.y += e->p.mov.y;
		e->col.y /= (e->keys[SDLK_LSHIFT % 42] ? 1.5 : 2);
	}
	else if (e->col.a2 == 0)
	{
		e->col.y = 0;
		e->col.x += e->p.mov.x;
		e->col.x /= (e->keys[SDLK_LSHIFT % 42] ? 1.5 : 2);
	}
	return (TRUE);
}

int			collision_handler(t_env *e)
{
	float	wall_angle;
	float	player_angle;
	float	angle_diff;
	float	mult;

	e->col.a1 = (e->col.p2.y - e->col.p1.y) / (e->col.p2.x - e->col.p1.x);
	e->col.a2 = (e->col.p4.y - e->col.p3.y) / (e->col.p4.x - e->col.p3.x);
	e->col.b1 = e->col.p1.y - (e->col.a1 * e->col.p1.x);
	e->col.b2 = e->col.p3.y - (e->col.a2 * e->col.p3.x);
	if (isinf(e->col.a2) || e->col.a2 == 0)
		first_cases(e);
	else
	{
		player_angle = atan(e->col.a1);
		wall_angle = atan(e->col.a2);
		e->col.sx = cos(wall_angle)
				* sqrt(e->p.mov.x * e->p.mov.x + e->p.mov.y * e->p.mov.y);
		e->col.sy = sin(wall_angle)
				* sqrt(e->p.mov.x * e->p.mov.x + e->p.mov.y * e->p.mov.y);
		angle_diff = fabs(wall_angle - player_angle);
		mult = fabs(90 - (57.2958 * angle_diff)) / 200;
		if (!second_cases(e, angle_diff, mult))
			third_cases(e, angle_diff, mult);
	}
	return (TRUE);
}
