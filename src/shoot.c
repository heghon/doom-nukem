/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 18:10:17 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/09 23:41:09 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	calc_z(t_env *env, t_point a, t_point b)
{
	t_float	dir;
	t_float	inter;
	float	k;
	float	cam;

	dir.x = env->p.dir.x * 10000;
	dir.y = env->p.dir.y * 10000;
	inter = inter_position_f(a, b, env->p.pos, dir);
	k = (float)(inter.x - env->p.pos.x) / env->p.dir.x;
	cam = (float)((SIDE * env->p.cam) - (float)(SIDE / 2)) / SIDE;
	return ((20 * env->p.pos.z) + k * cam);
}

static int	in_test_wall_before(t_env *env, t_point a, t_point b, int j)
{
	float	z;
	t_float	dir;
	t_point	pos[2];
	int		v;

	v = env->rend.see;
	dir.x = env->p.dir.x * 10000;
	dir.y = env->p.dir.y * 10000;
	pos[0] = env->rend.wall[v][j].w.pos;
	pos[1] = env->rend.wall[v][env->rend.wall[v][j].next].w.pos;
	while (env->rend.wall[v][j].next != env->rend.all && !equal(pos[0], a)
		&& !equal(pos[1], b) && !equal(pos[0], b) && !equal(pos[1], a))
	{
		pos[0] = env->rend.wall[v][j].w.pos;
		pos[1] = env->rend.wall[v][env->rend.wall[v][j].next].w.pos;
		if (segment_inter_f(pos[0], pos[1], env->p.pos, dir))
		{
			z = calc_z(env, pos[0], pos[1]);
			if (z >= env->rend.wall[v][j].w.floor
						&& z <= env->rend.wall[v][j].w.ceiling)
				return (0);
		}
		j = env->rend.wall[v][j].next;
	}
	return (env->rend.wall[v][j].next != env->rend.all ? 1 : ERROR);
}

static int	test_wall_before(t_env *env, t_point a, t_point b, int v)
{
	int		i;
	int		j;
	int		ret;

	i = env->rend.first_bunch[v];
	while (i != -1 && i != env->rend.all)
	{
		j = env->rend.bunch[v][i].start_wall;
		ret = in_test_wall_before(env, a, b, j);
		if (ret != ERROR)
			return (ret);
		i = env->rend.bunch[v][i].next;
	}
	return (1);
}

void		test_shoot(t_env *e)
{
	int		i;
	float	z;
	t_float	dir;

	dir.x = e->p.dir.x * 10000;
	dir.y = e->p.dir.y * 10000;
	i = -1;
	while (++i < e->card[e_character])
	{
		z = calc_z(e, e->character[i].o.a.pos, e->character[i].o.b.pos);
		if (segment_inter_f(e->character[i].o.a.pos, e->character[i].o.b.pos,
			e->p.pos, dir) && z >= e->character[i].o.b.floor
			&& z <= e->character[i].o.b.ceiling && test_wall_before(e,
			e->character[i].o.a.pos, e->character[i].o.b.pos, 0)
			&& test_wall_before(e, e->character[i].o.a.pos,
			e->character[i].o.b.pos, 1))
		{
			e->character[i].dead = 1;
			if (e->character[0].dead == 1)
			{
				e->character[0].dead = 0;
				e->p.new_level = e->nb_level - 1;
			}
		}
	}
}
