/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseneca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 21:34:12 by sseneca           #+#    #+#             */
/*   Updated: 2019/11/24 21:34:13 by sseneca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <math.h>
#include <unistd.h>

float	pythagore2(float ab, float cd)
{
	float ret;

	ret = sqrt(ab * ab + cd * cd);
	return (ret == ret ? ret : 1);
}

float	pythagore4(float a, float b, float c, float d)
{
	float ret;

	ret = pythagore2(b - a, d - c);
	return (ret == ret ? ret : 1);
}

void	draw_ceiling(t_env *env, t_utils *u, unsigned int *layer, t_texture *t)
{
	int		y;
	int		wy;
	t_float	pos;
	t_point	p;

	y = u->end >= SIDE ? SIDE - 1 : u->end;
	wy = SIDE * y + u->screenx;
	u->tex_u[0] = 20 / t->size;
	u->tex_u[1] = (env->p.pos.x - u->corner.x) / t->size;
	u->tex_u[2] = (env->p.pos.y - u->corner.y) / t->size;
	while (y >= 0 && layer[wy] == 0)
	{
		pos.x = u->dir.x * u->dist[1][y] + u->tex_u[1];
		pos.y = u->dir.y * u->dist[1][y] + u->tex_u[2];
		p.x = (int)((float)(pos.x - (int)pos.x) * t->w);
		p.y = (int)((float)(pos.y - (int)pos.y) * t->h);
		layer[wy] = color_tex(t->picture,
				4 * (p.x * t->w + p.y), u->lum);
		wy -= SIDE;
		y--;
	}
}

void	draw_floor(t_env *env, t_utils *u, unsigned int *layer, t_texture *tx)
{
	int		y;
	int		wy;
	t_float	pos;
	t_point	t;

	y = u->start >= SIDE ? SIDE - 1 : u->start;
	wy = SIDE * y + u->screenx;
	u->tex_u[0] = 20 / tx->size;
	u->tex_u[1] = (env->p.pos.x - u->corner.x) / tx->size;
	u->tex_u[2] = (env->p.pos.y - u->corner.y) / tx->size;
	while (y < SIDE && layer[wy] == 0)
	{
		pos.x = u->dir.x * u->dist[0][y] + u->tex_u[1];
		pos.y = u->dir.y * u->dist[0][y] + u->tex_u[2];
		t.x = (int)((float)(pos.x - (int)pos.x) * tx->w);
		t.y = (int)((float)(pos.y - (int)pos.y) * tx->h);
		layer[wy] = color_tex(tx->picture,
				4 * (t.x * tx->w + t.y), u->lum);
		wy += SIDE;
		y++;
	}
}
