/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmenant <bmenant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 11:37:01 by bmenant           #+#    #+#             */
/*   Updated: 2019/11/17 02:33:19 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	ft_mod(t_env *env, int i)
{
	if ((i - env->sector[env->wall[i - 1].sector].num_walls)
			== env->sector[env->wall[i - 1].sector].start_wall)
		return (env->sector[env->wall[i - 1].sector].start_wall);
	return (i);
}

int			double_wall(t_env *e)
{
	int i;

	e->col.p1.x = e->p.pos.x;
	e->col.p1.y = e->p.pos.y;
	e->col.p2.x = e->p.pos.x + e->col.x * 1;
	e->col.p2.y = e->p.pos.y + e->col.y * 1;
	i = e->sector[e->current_sector].start_wall - 1;
	while (++i < e->card[e_wall])
	{
		i += (i == e->col.current_wall ? 1 : 0);
		e->col.p3.x = (float)e->wall[i].pos.x;
		e->col.p3.y = (float)e->wall[i].pos.y;
		e->col.p4.x = (float)e->wall[ft_mod(e, i + 1)].pos.x;
		e->col.p4.y = (float)e->wall[ft_mod(e, i + 1)].pos.y;
		e->bb[i] = bound_box_creation(e->bb[i], e->col.p3, e->col.p4);
		if (hitbox_handler(e, i) && step_check(e, i)
				&& int_seg_seg(e->col.p1, e->col.p2, e->col.p3, e->col.p4))
			return (FALSE);
	}
	return (TRUE);
}
