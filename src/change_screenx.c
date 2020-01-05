/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_screenx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:18:36 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/06 02:20:09 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	calc_behind_fov(t_env *env, t_wall *w[2], int a, int b)
{
	t_float	ray;

	if ((w[1]->screenx < SIDE / 2 && a < b)
							|| (w[1]->screenx > SIDE / 2 && a > b))
		w[0]->screenx = a;
	else
	{
		ray.x = env->p.pos.x + env->p.dir.x * 10000;
		ray.y = env->p.pos.y + env->p.dir.y * 10000;
		if (segment_inter_f(w[0]->pos, w[1]->pos, env->p.pos, ray))
			w[0]->screenx = a;
		else
			w[0]->screenx = b;
	}
}

static void	change_point(t_env *env, t_wall *i, t_wall *j)
{
	t_float	point;

	if (i->screenx == 0)
	{
		point.x = env->p.pos.x + env->p.left.x * 10000;
		point.y = env->p.pos.y + env->p.left.y * 10000;
	}
	else
	{
		point.x = env->p.pos.x + env->p.right.x * 10000;
		point.y = env->p.pos.y + env->p.right.y * 10000;
	}
	point = inter_position_f(i->pos, j->pos, env->p.pos, point);
	i->pos.x = point.x + 0.5;
	i->pos.y = point.y + 0.5;
	i->p.x = point.x;
	i->p.y = point.y;
}

static void	calc_fov(t_env *env, t_wall *i, t_wall *j)
{
	float	right;
	float	left;
	float	dir;
	t_float	vec;
	t_wall	*w[2];

	w[0] = i;
	w[1] = j;
	vec.x = w[0]->pos.x - env->p.pos.x;
	vec.y = w[0]->pos.y - env->p.pos.y;
	left = vec.y * env->p.left.x - vec.x * env->p.left.y;
	right = vec.y * env->p.right.x - vec.x * env->p.right.y;
	dir = vec.y * env->p.dir.x - vec.x * env->p.dir.y;
	if (left > 0 && right > 0)
		w[0]->screenx = SIDE;
	else if (left < 0 && right < 0)
		w[0]->screenx = 0;
	else if (right >= 0 && dir <= 0)
		calc_behind_fov(env, w, 0, SIDE);
	else if (dir > 0 && left < 0)
		calc_behind_fov(env, w, SIDE, 0);
	else
		w[0]->screenx = w[0]->screenx > 0 ? SIDE : 0;
	change_point(env, w[0], w[1]);
}

void		tcheck_hors_fov(t_env *env, t_wall *i, t_wall *j)
{
	i->previous_pos = i->pos;
	j->previous_pos = j->pos;
	if (i->screenx > SIDE || i->screenx < 0)
		calc_fov(env, i, j);
	if (j->screenx > SIDE || j->screenx < 0)
		calc_fov(env, j, i);
	if (i->p.x == 0 && i->p.y == 0)
	{
		i->p.x = i->pos.x;
		i->p.y = i->pos.y;
	}
	if (j->p.x == 0 && j->p.y == 0)
	{
		j->p.x = j->pos.x;
		j->p.y = j->pos.y;
	}
}

void		screen_x(t_env *env, t_wall *wall)
{
	t_float	vec;
	float	dot;
	float	angle;

	vec.x = wall->pos.x - env->p.pos.x;
	vec.y = wall->pos.y - env->p.pos.y;
	dot = env->p.left.x * vec.x + env->p.left.y * vec.y;
	angle = acos((float)(dot / (sqrt((vec.x * vec.x)
		+ (vec.y * vec.y)) * sqrt((env->p.left.x * env->p.left.x)
		+ (env->p.left.y * env->p.left.y))))) * (float)(180 / M_PI);
	if (dot == 0)
		angle = (float)1 / (SIDE / FOV);
	if ((vec.y * env->p.left.x - vec.x * env->p.left.y < 0))
		angle = -angle;
	wall->screenx = (float)(angle * SIDE / FOV);
}
