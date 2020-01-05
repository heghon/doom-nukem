/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:08:06 by bmenant           #+#    #+#             */
/*   Updated: 2019/12/09 20:30:00 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <math.h>

int			collision_point(t_env *e)
{
	t_float v1;
	t_float v2;

	v1.x = e->col.p2.x - e->col.p1.x;
	v1.y = e->col.p2.y - e->col.p1.y;
	v2.x = e->col.p4.x - e->col.p3.x;
	v2.y = e->col.p4.y - e->col.p3.y;
	e->col.k = -(e->col.p1.x * v2.y - e->col.p3.x * v2.y - v2.x * e->col.p1.y +
			v2.x * e->col.p3.y) / (v1.x * v2.y - v1.y * v2.x);
	e->col.l = -(v1.x * e->col.p1.y + v1.x * e->col.p3.y + v1.y * e->col.p1.y -
			v1.y * e->col.p3.x) / (v1.x * v2.y - v1.y * v2.x);
	if (isnan(e->col.k))
	{
		e->p.pos.x += 0.1;
		e->p.pos.y += 0.1;
		collision_check(e);
	}
	if (e->col.k < 0 || e->col.k > 1)
		return (FALSE);
	return (TRUE);
}

int			step_check(t_env *e, int i)
{
	if ((e->p.state == stand || e->p.state == crouch)
			&& e->wall[i].next_sector == -1
			&& (((float)(e->wall[i].ceiling) / 20.0 + 0.5) - e->p.pos.z > 0.25))
		return ((e->p.pos.z - ((float)(e->wall[i].floor) / 20.0 - 0.1)) < 0.0 ?
				FALSE : TRUE);
	else if ((e->p.state == jump || e->p.state == fly)
			&& e->wall[i].next_sector == -1
				&& (((float)(e->wall[i].ceiling) / 20.0 + 0.5) > e->p.pos.z))
		return ((e->p.pos.z < ((float)(e->wall[i].floor) / 20.0 - 0.1)) ?
				FALSE : TRUE);
	else
	{
		if (e->wall[i].next_sector != -1 &&
			(e->p.pos.z < (float)(e->sector[e->wall[i].next_sector].floor) /
			20.0 + 0.24 || e->p.pos.z >
			(e->sector[e->wall[i].next_sector].ceiling) / 20.0 - 0.1))
			return (TRUE);
		else
			return (FALSE);
	}
}

int			collision_check(t_env *e)
{
	int		ret;

	e->col.k = 1;
	e->col.l = 1;
	e->col.x = 0;
	e->col.y = 0;
	e->col.p1.x = e->p.pos.x;
	e->col.p1.y = e->p.pos.y;
	e->col.p2.x = e->p.pos.x + (e->p.mov.x * 1);
	e->col.p2.y = e->p.pos.y + (e->p.mov.y * 1);
	ret = int_check(e);
	if (ret == 1)
		return (collision_handler(e));
	if (ret == 2)
		return (2);
	return (TRUE);
}
