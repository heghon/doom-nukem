/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bunch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 23:59:13 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/10 00:10:03 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		add_to_bunch2(t_env *env, t_wall i, t_wall j, int first)
{
	t_render	*r;
	int			v;

	r = &env->rend;
	v = r->see;
	tcheck_hors_fov(env, &i, &j);
	if (r->cur[v][e_w] == -1
		|| !(equal(r->wall[v][r->bunch[v]
				[r->cur[v][e_b]].start_wall].w.pos, i.pos))
		|| first == 1)
	{
		first_wall(env, i);
		r->wall[v][r->cur[v][e_w]].next = env->rend.all;
	}
	r->cur[v][e_w]++;
	r->bunch[v][r->cur[v][e_b]].sector = j.sector;
	r->wall[v][r->cur[v][e_w]].w = j;
	r->wall[v][r->cur[v][e_w]].next = r->bunch[v][r->cur[v][e_b]].start_wall;
	r->bunch[v][r->cur[v][e_b]].start_wall = r->cur[v][e_w];
}

void		add_to_bunch1(t_env *env, t_wall i, t_wall j, int first)
{
	t_render	*r;
	int			v;
	int			tmp;

	r = &env->rend;
	v = r->see;
	tcheck_hors_fov(env, &i, &j);
	if (j.next_sector != -1)
		j.next_sector = -1;
	if (i.next_sector != -1)
	{
		tmp = i.next_sector;
		i.next_sector = j.next_sector;
		j.next_sector = tmp;
	}
	if (r->cur[v][e_w] == -1
		|| !(equal(r->wall[v][r->cur[v][e_w]].w.pos, i.pos)) || first == 1)
		first_wall(env, i);
	r->wall[v][r->cur[v][e_w]].next = r->cur[v][e_w] + 1;
	r->cur[v][e_w]++;
	r->wall[v][r->cur[v][e_w]].w = j;
	r->wall[v][r->cur[v][e_w]].next = env->rend.all;
}

static int	test_visible(t_env *env, int l_to_r, int i, int j)
{
	int first;
	int	in_sector;

	in_sector = (env->wall[i].sector == env->rend.sector) ? TRUE
								: is_in_sector(env, env->wall[i].sector);
	first = 0;
	if (env->sector[env->wall[i].sector].start_wall == i)
		first = 1;
	if ((!l_to_r && in_sector && env->wall[i].ceiling > env->p.pos.z * 20
		&& env->wall[i].floor < env->p.pos.z * 20)
		|| (l_to_r && !in_sector)
		|| (l_to_r && in_sector && env->wall[i].ceiling < env->p.pos.z * 20
		&& env->rend.port == OFF)
		|| (l_to_r && in_sector && env->wall[i].floor > env->p.pos.z * 20
		&& env->rend.port == OFF)
		|| (!l_to_r && in_sector && env->rend.port == ON))
	{
		env->rend.see = visible;
		if (l_to_r)
			add_to_bunch1(env, env->wall[i], env->wall[j], first);
		else
			add_to_bunch2(env, env->wall[i], env->wall[j], first);
		return (1);
	}
	return (0);
}

static void	test_invisible(t_env *env, int l_to_r, int i, int j)
{
	int first;
	int	in_sector;

	in_sector = (env->wall[i].sector == env->rend.sector) ? TRUE
								: is_in_sector(env, env->wall[i].sector);
	first = 0;
	if (env->sector[env->wall[i].sector].start_wall == i)
		first = 1;
	if ((!l_to_r && in_sector && env->wall[i].ceiling < env->p.pos.z * 20)
		|| (!l_to_r && !in_sector && env->wall[i].ceiling < env->p.pos.z * 20)
		|| (!l_to_r && !in_sector && env->wall[i].floor > env->p.pos.z * 20)
		|| (!l_to_r && in_sector && env->wall[i].floor > env->p.pos.z * 20))
	{
		env->rend.see = invisible;
		if (l_to_r)
			add_to_bunch1(env, env->wall[i], env->wall[j], first);
		else
			add_to_bunch2(env, env->wall[i], env->wall[j], first);
	}
}

/*
**setup sprite a un autre endroit
*/

void		create_bunch(t_env *e)
{
	int i;
	int	j;
	int	sect;
	int	l_to_r;

	i = -1;
	init_render(e);
	while (++i < e->card[e_wall])
	{
		sect = which_sector(e, i);
		j = next_j(e, i, e->wall[i].sector);
		if (is_in_range(e, e->wall[i], e->wall[j]) && sect == e->rend.sector
			&& (e->wall[i].floor >= e->sector[e->rend.sector].floor)
			&& (e->wall[i].ceiling <= e->sector[e->rend.sector].ceiling))
		{
			l_to_r = left_to_right(&e->p, e->wall[i].pos, e->wall[j].pos);
			if (!test_visible(e, l_to_r, i, j))
				test_invisible(e, l_to_r, i, j);
			if (j != i + 1)
				push_bunch(e, e->wall[j].sector, l_to_r);
		}
	}
	setup_sprite(e);
	e->rend.see = invisible;
	sort_bunch(e);
}
