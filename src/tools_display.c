/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 00:42:30 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/07 23:37:27 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <math.h>
#include <unistd.h>

void	choose_floor_ceiling(t_env *env, t_utils *u, int mode)
{
	if (mode == 0)
		draw_floor(env, u, (unsigned int *)env->view.layer[render_layer],
				&env->texture[env->sector[u->a.sector].tex_c]);
	else if (mode == 1)
		draw_ceiling(env, u, (unsigned int *)env->view.layer[render_layer],
				&env->texture[env->sector[u->a.sector].tex_f]);
	else if (mode == 2)
	{
		u->inc = -env->p.pos.z + (u->a.floor / 20.0);
		draw_f_main(env, u, (unsigned int *)env->view.layer
				[render_layer], &env->texture
				[env->sector[env->rend.sector].tex_f]);
		u->inc = (1 - env->p.pos.z) + ((u->a.ceiling) / 20.0 - 1);
		draw_c_main(env, u, (unsigned int *)env->view.layer
				[render_layer], &env->texture
				[env->sector[env->rend.sector].tex_c]);
	}
}

void	check_float(float *f, int max)
{
	*f = *f > max ? max : *f;
	*f = *f < -max ? -max : *f;
	*f = *f == *f ? *f : 0;
}

void	prepare_floor_ceiling(t_env *env, t_utils *u, int mode)
{
	t_float	left;
	float	beta;
	float	ang;

	prepare_dist(env, u);
	ang = (((2 * ANGLE_VISION) / (float)SIDE) * u->screenx);
	beta = fabs(ang - ANGLE_VISION);
	left.x = env->p.left.x * cos(beta);
	left.y = env->p.left.y * cos(beta);
	left.x = env->p.left.x + (float)(env->p.left.x - left.x);
	left.y = env->p.left.y + (float)(env->p.left.y - left.y);
	u->dir.x = left.x * cos(ang) - left.y * sin(ang);
	u->dir.y = left.x * sin(ang) + left.y * cos(ang);
	if (mode == 0 || mode == 1)
		u->inc = mode == 0 ? -env->p.pos.z + (u->a.ceiling / 20.0)
			: (1 - env->p.pos.z) + ((u->a.floor) / 20.0 - 1);
	choose_floor_ceiling(env, u, mode);
}

void	prepare_dist(t_env *env, t_utils *u)
{
	int		i;
	float	inc[4];

	i = -1;
	inc[0] = (-env->p.pos.z + (u->a.ceiling / 20.0))
		* (20 / env->texture[env->sector[u->a.sector].tex_c].size);
	inc[1] = ((1 - env->p.pos.z) + ((u->a.floor) / 20.0 - 1))
		* (20 / env->texture[env->sector[u->a.sector].tex_f].size);
	inc[2] = (-env->p.pos.z + (u->a.floor / 20.0))
		* (20 / env->texture[env->sector[u->a.sector].tex_f].size);
	inc[3] = ((1 - env->p.pos.z) + (u->a.ceiling / 20.0 - 1))
		* (20 / env->texture[env->sector[u->a.sector].tex_c].size);
	while (++i < SIDE)
	{
		u->dist[0][i] = inc[0] / (env->p.cam - (i / (float)SIDE));
		check_float(&u->dist[0][i], MAX_DIST);
		u->dist[1][i] = inc[1] / (env->p.cam - (i / (float)SIDE));
		check_float(&u->dist[1][i], MAX_DIST);
		u->dist[2][i] = inc[2] / (env->p.cam - (i / (float)SIDE));
		check_float(&u->dist[2][i], MAX_DIST);
		u->dist[3][i] = inc[3] / (env->p.cam - (i / (float)SIDE));
		check_float(&u->dist[3][i], MAX_DIST);
	}
}

void	portal_handler(t_env *env, t_utils *u, t_texture *tex)
{
	float	dist[2];
	float	coeff;
	int		sector[2];
	int		port[2];

	sector[0] = u->b.next_sector;
	sector[1] = u->b.sector;
	find_portal(env, sector, &port[0], &port[1]);
	dist[0] = pythagore4(u->old_b.x, u->old_a.x, u->old_b.y, u->old_a.y);
	dist[1] = pythagore4(env->wall[port[0]].pos.x, env->wall[port[1]].pos.x,
							env->wall[port[0]].pos.y, env->wall[port[1]].pos.y);
	if (dist[0] != 0 && dist[1] != 0
		&& dist[0] > dist[1] && dist[0] < 2147483647 && dist[1] < 2147483647)
	{
		coeff = (1 - dist[1] / dist[0]) / 2;
		if (coeff >= u->coeff / dist[0] || (1 - coeff) <= u->coeff / dist[0])
		{
			draw_wall(u, (unsigned int *)env->view.layer[render_layer], tex);
			return ;
		}
	}
	draw_portal(env, u, (unsigned int *)env->view.layer[render_layer], tex);
}
