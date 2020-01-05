/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_bunch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:25:08 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/09 20:27:54 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	first_in_sec(t_env *env, int i, int j)
{
	int	v;

	v = env->rend.see;
	if (env->rend.wall[v][i].w.sector != -1
		&& env->rend.wall[v][j].w.sector != -1
		&& point_in_sector(env, env->rend.wall[v][j].w.sector,
			env->rend.wall[v][i].w.pos)
		&& env->rend.sector != env->rend.wall[v][j].w.sector
		&& env->rend.wall[v][i].w.floor >= env->rend.wall[v][j].w.floor
		&& env->rend.wall[v][i].w.ceiling <= env->rend.wall[v][j].w.ceiling
		&& env->rend.sector != env->rend.wall[v][j].w.sector
		&& !same_wall(env, env->rend.wall[v][j].w.sector,
			env->rend.wall[v][i].w.pos)
		&& env->rend.wall[v][i].w.sector != env->rend.wall[v][j].w.sector)
		return (TRUE);
	return (FALSE);
}

static int	closest_bunch(t_env *env, int first, int sec)
{
	int	i;
	int	j;
	int	ret;

	i = env->rend.bunch[env->rend.see][first].start_wall;
	while (env->rend.wall[env->rend.see][i].next != env->rend.all)
	{
		j = env->rend.bunch[env->rend.see][sec].start_wall;
		while (env->rend.wall[env->rend.see][j].next != env->rend.all)
		{
			if (first_in_sec(env, j, i))
				return (TRUE);
			if (first_in_sec(env, i, j))
				return (FALSE);
			if (overlap(env, i, j))
			{
				ret = closest_wall(env, i, j, env->rend.see);
				if (ret != ERROR)
					return (ret);
			}
			j = env->rend.wall[env->rend.see][j].next;
		}
		i = env->rend.wall[env->rend.see][i].next;
	}
	return (ERROR);
}

int			test_height_sector(t_env *env, int i, int j, int vision)
{
	int floor[2];
	int ceiling[2];
	int	v;
	int v1;

	v = vision == 1 ? invisible : env->rend.see;
	v1 = vision == 1 ? visible : env->rend.see;
	floor[0] = env->rend.wall[v][env->rend.bunch[v][i].start_wall].w.floor;
	floor[1] = env->rend.wall[v1][env->rend.bunch[v1][j].start_wall].w.floor;
	ceiling[0] = env->rend.wall[v][env->rend.bunch[v][i].start_wall].w.ceiling;
	ceiling[1] = env->rend.wall[v1]
								[env->rend.bunch[v1][j].start_wall].w.ceiling;
	if (env->p.pos.z * 20 < ceiling[0] && ceiling[0] <= floor[1])
		return (TRUE);
	if (env->p.pos.z * 20 < ceiling[1] && ceiling[1] <= floor[0])
		return (FALSE);
	if (env->p.pos.z * 20 >= floor[1] && floor[1] > ceiling[0])
		return (FALSE);
	if (env->p.pos.z * 20 >= floor[0] && floor[0] > ceiling[1])
		return (TRUE);
	return (ERROR);
}

static int	first_tests(t_env *env, int i, int j)
{
	int	ret;
	int	v;

	v = env->rend.see;
	ret = test_height_sector(env, i, j, 0);
	if (ret != ERROR)
		return (ret);
	ret = closest_bunch(env, i, j);
	if (ret != ERROR || env->rend.see == invisible)
		return (ret);
	if (env->rend.wall[v][env->rend.bunch[v][i].start_wall].w.sector == -1
		&& env->rend.wall[v][env->rend.bunch[v][j].start_wall].w.sector == -1)
		return (dist_bunch(env, i, j));
	return (ERROR);
}

int			closest_bunch1(t_env *env, int i, int j)
{
	int	ret;
	int	bunch;
	int	bunch1;

	ret = first_tests(env, i, j);
	if (ret != ERROR)
		return (ret);
	bunch = first_bunch(env, i);
	while (bunch != env->rend.all)
	{
		bunch1 = first_bunch(env, j);
		while (bunch1 != env->rend.all)
		{
			ret = closest_bunch(env, bunch, bunch1);
			if (ret != -1)
				return (ret);
			bunch1 = next_bunch(env, bunch1, j);
		}
		bunch = next_bunch(env, bunch, i);
	}
	return (dist_bunch(env, i, j));
}
