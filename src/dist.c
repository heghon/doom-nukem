/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:31:32 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/07 02:51:41 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <math.h>

float	dist_wall(t_env *env, t_float point)
{
	float	dist;
	t_float	vec;
	float	dot;
	float	angle;

	dist = sqrt(((point.x - env->p.pos.x)
				* (point.x - env->p.pos.x))
			+ ((point.y - env->p.pos.y)
				* (point.y - env->p.pos.y)));
	vec.x = point.x - env->p.pos.x;
	vec.y = point.y - env->p.pos.y;
	dot = env->p.dir.x * vec.x + env->p.dir.y * vec.y;
	angle = (float)(dot / (sqrt((vec.x * vec.x)
					+ (vec.y * vec.y)) * sqrt((env->p.dir.x * env->p.dir.x)
					+ (env->p.dir.y * env->p.dir.y))));
	dist *= angle;
	dist = (float)(dist / 20);
	dist = dist < 0.0001 ? 0.0001 : dist;
	dist = dist > 2147483647 ? 2147483647 : dist;
	return (dist);
}

float	ft_dist(t_env *env, t_float point)
{
	float	dist;

	dist = sqrt((point.x - env->p.pos.x) * (point.x - env->p.pos.x)
		+ (point.y - env->p.pos.y) * (point.y - env->p.pos.y));
	return (dist);
}

int		dist_bunch(t_env *env, int i, int j)
{
	int		bunch;
	float	dist;
	float	dist1;
	float	tmp;

	bunch = env->rend.bunch[env->rend.see][i].start_wall;
	dist = ft_dist(env, env->rend.wall[env->rend.see][bunch].w.p);
	while (bunch != env->rend.all)
	{
		tmp = ft_dist(env, env->rend.wall[env->rend.see][bunch].w.p);
		dist = tmp < dist ? tmp : dist;
		bunch = env->rend.wall[env->rend.see][bunch].next;
	}
	bunch = env->rend.bunch[env->rend.see][j].start_wall;
	dist1 = ft_dist(env, env->rend.wall[env->rend.see][bunch].w.p);
	while (bunch != env->rend.all)
	{
		tmp = ft_dist(env, env->rend.wall[env->rend.see][bunch].w.p);
		dist1 = tmp < dist1 ? tmp : dist1;
		bunch = env->rend.wall[env->rend.see][bunch].next;
	}
	if (dist <= dist1)
		return (TRUE);
	return (FALSE);
}
