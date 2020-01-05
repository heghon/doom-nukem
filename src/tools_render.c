/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:33:02 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/09 23:44:15 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		equal(t_point first, t_point sec)
{
	if (first.x == sec.x && first.y == sec.y)
		return (TRUE);
	return (FALSE);
}

int		left_to_right(t_player *p, t_point first, t_point sec)
{
	t_float	f;
	t_float	s;
	float	op;
	float	k;

	f.x = first.x - p->pos.x;
	f.y = first.y - p->pos.y;
	s.x = sec.x - p->pos.x;
	s.y = sec.y - p->pos.y;
	op = s.y * f.x - s.x * f.y;
	if (op == 0)
	{
		if (s.x != 0 && f.x != 0)
		{
			k = (float)f.x / s.x;
			return (k > 0 ? TRUE : FALSE);
		}
		k = (float)f.y / s.y;
		return (k > 0 ? TRUE : FALSE);
	}
	if (op < 0)
		return (FALSE);
	return (TRUE);
}

void	first_wall(t_env *env, t_wall i)
{
	int v;

	v = env->rend.see;
	if (env->rend.cur[v][e_b] != -1)
		env->rend.bunch[v]
			[env->rend.cur[v][e_b]].next = env->rend.cur[v][e_b] + 1;
	else
		env->rend.first_bunch[v] = 0;
	env->rend.cur[v][e_b]++;
	env->rend.cur[v][e_w]++;
	env->rend.bunch[v]
		[env->rend.cur[v][e_b]].start_wall = env->rend.cur[v][e_w];
	env->rend.bunch[v][env->rend.cur[v][e_b]].next = env->rend.all;
	env->rend.wall[v][env->rend.cur[v][e_w]].w = i;
}

int		next_j(t_env *env, int i, int sector)
{
	int j;

	if (sector == env->card[e_sector] - 1)
		j = i == env->card[e_wall] - 1 ? env->sector[sector].start_wall : i + 1;
	else
		j = (i == env->sector[sector + 1].start_wall - 1) ? env->sector
													[sector].start_wall : i + 1;
	return (j);
}

void	port_same_xy(t_env *env, t_float perp, float dist, int port[2])
{
	env->p.pos.x = perp.z == 1 ? perp.x + dist : perp.x;
	env->p.pos.y = perp.z == 1 ? perp.y : dist + perp.y;
	if (left_to_right(&env->p, env->wall[port[0]].pos, env->wall[port[1]].pos))
		return ;
	env->p.pos.x = perp.z == 1 ? perp.x - dist : perp.x;
	env->p.pos.y = perp.z == 1 ? perp.y : perp.y - dist;
}
