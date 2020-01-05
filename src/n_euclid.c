/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_euclid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 00:02:34 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/06 23:45:04 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	new_perp(t_env *env, t_float *perp, t_wall w[2], int port[2])
{
	t_float	mil;
	t_float mil1;
	float	dist1;
	float	dist2;
	t_float	vec;

	w[1].pos = w[1].previous_pos;
	w[0].pos = w[0].previous_pos;
	mil.x = w[1].pos.x + (float)(w[0].pos.x - w[1].pos.x) / 2;
	mil.y = w[1].pos.y + (float)(w[0].pos.y - w[1].pos.y) / 2;
	mil1.x = env->wall[port[0]].pos.x
			+ (float)(env->wall[port[1]].pos.x - env->wall[port[0]].pos.x) / 2;
	mil1.y = env->wall[port[0]].pos.y
			+ (float)(env->wall[port[1]].pos.y - env->wall[port[0]].pos.y) / 2;
	dist1 = sqrt(((perp->x - mil.x) * (perp->x - mil.x)) +
		((perp->y - mil.y) * (perp->y - mil.y)));
	vec.x = mil1.x - env->wall[port[1]].pos.x;
	vec.y = mil1.y - env->wall[port[1]].pos.y;
	dist2 = w[1].pos.x - w[0].pos.x;
	if ((dist2 && (perp->x - mil.x) / (dist2) > 0)
		|| (!dist2 && (perp->y - mil.y) / (w[1].pos.y - w[0].pos.y) > 0))
		dist1 = -dist1;
	dist2 = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	perp->x = mil1.x + ((float)(dist1 * (float)(vec.x / dist2)));
	perp->y = mil1.y + ((float)(dist1 * (float)(vec.y / dist2)));
}

static void	new_pos(t_env *env, t_wall w[2], int port[2])
{
	float	coeff;
	t_float	perp;
	float	param[2];

	param[1] = calc_dist(env, &perp, w[0], w[1]);
	new_perp(env, &perp, w, port);
	perp.z = 0;
	if (env->wall[port[0]].pos.x - env->wall[port[1]].pos.x
				&& env->wall[port[0]].pos.y - env->wall[port[1]].pos.y)
	{
		coeff = (float)(env->wall[port[0]].pos.y - env->wall[port[1]].pos.y)
				/ (env->wall[port[0]].pos.x - env->wall[port[1]].pos.x);
		param[0] = (float)(-1.0 / coeff);
		line_cercle_inter(env, param, perp, port);
		return ;
	}
	else if (env->wall[port[0]].pos.x == env->wall[port[1]].pos.x)
	{
		perp.z = 1;
		port_same_xy(env, perp, param[1], port);
		return ;
	}
	else
		port_same_xy(env, perp, param[1], port);
}

static void	new_dir(t_env *env, t_float vecc)
{
	t_float	vec;
	float	a;
	float	tmp;

	vec.x = env->rend.portal[env->rend.first_portal].j.previous_pos.x
				- env->rend.portal[env->rend.first_portal].i.previous_pos.x;
	vec.y = env->rend.portal[env->rend.first_portal].j.previous_pos.y
				- env->rend.portal[env->rend.first_portal].i.previous_pos.y;
	a = ft_angle(vecc, vec);
	tmp = env->p.dir.x;
	env->p.dir.x = env->p.dir.x * cos(a + M_PI) - env->p.dir.y * sin(a + M_PI);
	env->p.dir.y = tmp * sin(a + M_PI) + env->p.dir.y * cos(a + M_PI);
	init_fov(env);
}

void		new_cord(t_env *env)
{
	t_float	vec;
	int		sector[2];
	t_wall	w[2];
	int		port[2];

	if (!(same_wall(env, env->rend.portal[env->rend.first_portal].j.next_sector,
		env->rend.portal[env->rend.first_portal].j.previous_pos)))
	{
		env->rend.euc = ON;
		sector[0] = env->rend.portal[env->rend.first_portal].j.next_sector;
		sector[1] = env->rend.portal[env->rend.first_portal].j.sector;
		vec = find_portal(env, sector, &port[0], &port[1]);
		if (vec.x == 0 && vec.y == 0)
			return ;
		new_dir(env, vec);
		w[0] = env->rend.portal[env->rend.first_portal].i;
		w[1] = env->rend.portal[env->rend.first_portal].j;
		new_pos(env, w, port);
		env->p.pos.z = env->p.tmp_pos.z;
	}
}
