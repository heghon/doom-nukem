/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:23:19 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/09 20:29:17 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			overlap(t_env *env, int i, int j)
{
	float	starti;
	float	endi;
	float	startj;
	float	endj;
	int		v;

	v = env->rend.see;
	starti = env->rend.wall[v][i].w.screenx;
	endi = env->rend.wall[v][env->rend.wall[v][i].next].w.screenx;
	startj = env->rend.wall[v][j].w.screenx;
	endj = env->rend.wall[v][env->rend.wall[v][j].next].w.screenx;
	if ((starti >= startj && starti <= endj)
			|| (endi >= startj && endi <= endj)
			|| (startj >= starti && startj <= endi)
			|| (endj > starti && endj <= endi)
			|| (starti <= startj && starti >= endj)
			|| (endi <= startj && endi >= endj))
		return (TRUE);
	return (FALSE);
}

/*
**RAJOUTER MAX VALUES
*/

static void	seg_to_infinit(t_env *env, t_point *b, t_point *a, int wall)
{
	float	m;
	float	k;
	t_wall	w;
	t_wall	e;

	w = env->rend.wall[env->rend.see][wall].w;
	e = env->rend.wall[env->rend.see]
					[env->rend.wall[env->rend.see][wall].next].w;
	if (w.pos.x == e.pos.x)
	{
		a->x = w.pos.x;
		a->y = SIDE * 2;
		b->x = a->x;
		b->y = 0;
	}
	else
	{
		m = (float)((double)(e.pos.y - w.pos.y) / (e.pos.x - w.pos.x));
		k = w.pos.y - (m * w.pos.x);
		b->y = m * SIDE * 2 + k;
		b->x = SIDE * 2;
		a->y = k;
		a->x = 0;
	}
}

static int	test_angle(t_env *env, int i, int j)
{
	int	v;

	v = env->rend.see;
	if (equal(env->rend.wall[v][i].w.previous_pos,
		env->rend.wall[v][j].w.previous_pos))
		return (dist_wall(env, env->rend.wall[v][env->rend.wall[v][i].next].w.p)
			<= dist_wall(env, env->rend.wall[v][env->rend.wall[v][j].next].w.p)
			? TRUE : FALSE);
	else if (equal(env->rend.wall[v][env->rend.wall[v][i].next].w.previous_pos,
			env->rend.wall[v][env->rend.wall[v][j].next].w.previous_pos))
		return (dist_wall(env, env->rend.wall[v][i].w.p)
			<= dist_wall(env, env->rend.wall[v][j].w.p) ? TRUE : FALSE);
	else if (equal(env->rend.wall[v][i].w.previous_pos,
			env->rend.wall[v][env->rend.wall[v][j].next].w.previous_pos))
		return (dist_wall(env, env->rend.wall[v][env->rend.wall[v][i].next].w.p)
			<= dist_wall(env, env->rend.wall[v][j].w.p) ? TRUE : FALSE);
	else if (equal(env->rend.wall[v][env->rend.wall[v][i].next].w.previous_pos,
			env->rend.wall[v][j].w.previous_pos))
	{
		return (dist_wall(env, env->rend.wall[v][i].w.p) <= dist_wall(env,
			env->rend.wall[v][env->rend.wall[v][j].next].w.p) ? TRUE : FALSE);
	}
	return (ERROR);
}

static int	test_cross_lines(t_env *env, int i, int j)
{
	int v;

	v = env->rend.see;
	if (segment_inter(env->rend.wall[v][i].w.previous_pos,
		env->rend.wall[v][env->rend.wall[v][i].next].w.previous_pos,
		env->rend.wall[v][j].w.previous_pos,
		env->rend.wall[v][env->rend.wall[v][j].next].w.previous_pos))
		return (TRUE);
	return (FALSE);
}

int			closest_wall(t_env *env, int i, int j, int v)
{
	t_point	a;
	t_point	b;
	int		n[2];
	int		ret;

	n[0] = 0;
	n[1] = j;
	ret = test_angle(env, i, j);
	if (ret != ERROR)
		return (ret);
	if (test_cross_lines(env, i, j))
		return (ERROR);
	seg_to_infinit(env, &b, &a, i);
	if (segment_inter_f(a, b, env->rend.wall[v][j].w.p,
		env->rend.wall[v][env->rend.wall[v][j].next].w.p))
	{
		seg_to_infinit(env, &b, &a, j);
		n[0] = 1;
		n[1] = i;
	}
	if (segment_inter_f(a, b, env->rend.wall[v][n[1]].w.p, env->p.pos)
		|| segment_inter_f(a, b,
		env->rend.wall[v][env->rend.wall[v][n[1]].next].w.p, env->p.pos))
		return ((n[0] == 0) ? TRUE : FALSE);
	return ((n[0] == 0) ? FALSE : TRUE);
}
