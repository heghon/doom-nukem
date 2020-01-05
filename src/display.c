/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseneca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 21:34:03 by sseneca           #+#    #+#             */
/*   Updated: 2019/11/24 21:34:05 by sseneca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <math.h>
#include <unistd.h>

int		color_tex(unsigned char *pic, int p, float l)
{
	int ct;

	p = p < 0 ? 0 : p;
	ct = (int)(pic[p] * l) * 65536 + (int)(pic[p + 1] * l)
		* 256 + (int)(pic[p + 2] * l);
	if (ct == 0 && (pic[p] != 0 || pic[p + 1] != 0 || pic[p + 2] != 0))
		ct = 1;
	ct = ct < 0 ? 0 : ct;
	return (ct);
}

void	draw_portal(t_env *env, t_utils *u, unsigned int *layer, t_texture *tx)
{
	int		y;
	int		h;
	int		wy;
	float	diff;

	u->old_end += (u->pente * u->screenx + u->k) * (u->a.floor) / 20.0;
	diff = u->old_end - u->start;
	y = u->start < 0 ? 0 : u->start;
	wy = SIDE * y + u->screenx;
	while (y < u->end && y < SIDE)
	{
		if (layer[wy] == 0 && ((1 - (y - u->start) / diff) * u->a.ceiling
					> env->sector[u->b.next_sector].ceiling
					|| (1 - (y - u->start) / diff) * u->a.ceiling
					< env->sector[u->b.next_sector].floor))
		{
			h = tx->h * (y - u->start) / u->height;
			layer[wy] = color_tex(tx->picture, 4 * (h * tx->w + u->w), u->lum);
		}
		wy += SIDE;
		y++;
	}
}

void	draw_wall(t_utils *u, unsigned int *layer, t_texture *tx)
{
	int	y;
	int	h;
	int	wy;

	y = u->start < 0 ? 0 : u->start;
	wy = SIDE * y + u->screenx;
	while (y < u->end && y < SIDE)
	{
		if (layer[wy] == 0)
		{
			h = tx->h * (y - u->start) / u->height;
			layer[wy] = color_tex(tx->picture, 4 * (h * tx->w + u->w), u->lum);
		}
		wy += SIDE;
		y++;
	}
}

void	draw_c_main(t_env *env, t_utils *u, unsigned int *layer, t_texture *tx)
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
	while (y >= 0)
	{
		if (layer[wy] == 0)
		{
			pos.x = u->dir.x * u->dist[3][y] + u->tex_u[1];
			pos.y = u->dir.y * u->dist[3][y] + u->tex_u[2];
			t.x = (int)((float)(pos.x - (int)pos.x) * tx->w);
			t.y = (int)((float)(pos.y - (int)pos.y) * tx->h);
			layer[wy] = color_tex(tx->picture, 4 * (t.x * tx->w + t.y), u->lum);
		}
		wy -= SIDE;
		y--;
	}
}

void	draw_f_main(t_env *env, t_utils *u, unsigned int *layer, t_texture *tx)
{
	int		y;
	int		wy;
	t_float	pos;
	t_point	t;

	y = u->end < 0 ? 0 : u->end;
	wy = SIDE * y + u->screenx;
	u->tex_u[0] = 20 / tx->size;
	u->tex_u[1] = (env->p.pos.x - u->corner.x) / tx->size;
	u->tex_u[2] = (env->p.pos.y - u->corner.y) / tx->size;
	while (y < SIDE)
	{
		if (layer[wy] == 0)
		{
			pos.x = u->dir.x * u->dist[2][y] + u->tex_u[1];
			pos.y = u->dir.y * u->dist[2][y] + u->tex_u[2];
			t.x = (int)((float)(pos.x - (int)pos.x) * tx->w);
			t.y = (int)((float)(pos.y - (int)pos.y) * tx->h);
			layer[wy] = color_tex(tx->picture, 4 * (t.x * tx->w + t.y), u->lum);
		}
		wy += SIDE;
		y++;
	}
}
