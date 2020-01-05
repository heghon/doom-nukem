/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_bunch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:21:12 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/06 23:21:39 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	find_bunch(t_env *env, int sector, int left_to_right)
{
	int b;
	int	i;
	int	v;

	v = env->rend.see;
	b = env->rend.cur[v][e_b] - 1;
	while (b >= 0)
	{
		i = env->rend.bunch[v][b].start_wall;
		while (env->rend.wall[v][i].next != env->rend.all && !left_to_right)
			i = env->rend.wall[v][i].next;
		if (equal(env->rend.wall[env->rend.see][i].w.pos,
					env->wall[env->sector[sector].start_wall].pos)
					&& env->rend.wall[env->rend.see][i].w.sector == sector)
			return (b);
		b--;
	}
	return (ERROR);
}

static void	tools_push(t_env *env, int b, int b1)
{
	int	v;
	int	i;

	v = env->rend.see;
	i = env->rend.bunch[v][b1].start_wall;
	while (env->rend.wall[v][i].next != env->rend.all)
		i = env->rend.wall[v][i].next;
	env->rend.wall[v][i].next = env->rend.wall[v]
					[env->rend.bunch[v][b].start_wall].next;
}

void		push_bunch(t_env *env, int sector, int left_to_right)
{
	int	b;
	int	v;

	v = env->rend.see;
	if (env->rend.cur[v][e_b] == ERROR)
		return ;
	if (left_to_right)
	{
		b = find_bunch(env, sector, 1);
		if (b == ERROR)
			return ;
		tools_push(env, b, env->rend.cur[v][e_b]);
		env->rend.bunch[v][b].start_wall = env->rend.bunch[v]
								[env->rend.cur[v][e_b]].start_wall;
	}
	else
	{
		b = find_bunch(env, sector, 0);
		if (b == ERROR)
			return ;
		tools_push(env, env->rend.cur[v][e_b], b);
	}
	env->rend.cur[v][e_b]--;
	env->rend.bunch[v][env->rend.cur[v][e_b]].next = env->rend.all;
}

int			first_bunch(t_env *env, int i)
{
	int v;
	int bunch;

	v = env->rend.see;
	if (env->rend.wall[v][env->rend.bunch[v][i].start_wall].w.sector != -1
		&& env->rend.sector
		!= env->rend.wall[v][env->rend.bunch[v][i].start_wall].w.sector)
	{
		bunch = env->rend.first_bunch[v];
		while (env->rend.wall[v][env->rend.bunch[v][bunch].start_wall].w.sector
			!= env->rend.wall[v][env->rend.bunch[v][i].start_wall].w.sector
			&& bunch != env->rend.all)
			bunch = env->rend.bunch[v][bunch].next;
	}
	else
		bunch = i;
	return (bunch);
}

int			next_bunch(t_env *env, int bunch, int i)
{
	int	v;

	v = env->rend.see;
	if (env->rend.wall[v][env->rend.bunch[v][i].start_wall].w.sector != -1
		&& env->rend.sector
		!= env->rend.wall[v][env->rend.bunch[v][i].start_wall].w.sector)
	{
		bunch = env->rend.bunch[v][bunch].next;
		while (env->rend.wall[v][env->rend.bunch[v][bunch].start_wall].w.sector
				!= env->rend.wall[v][env->rend.bunch[v][i].start_wall].w.sector
				&& bunch != env->rend.all)
			bunch = env->rend.bunch[v][bunch].next;
	}
	else
		bunch = env->rend.all;
	return (bunch);
}
