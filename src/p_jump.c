/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_stand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmenant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:46:05 by bmenant           #+#    #+#             */
/*   Updated: 2019/11/08 18:20:07 by bmenant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	loop(t_env *e, int i)
{
	while (++i < e->card[e_sector])
	{
		i += (i == e->p.sector ? 1 : 0);
		if (is_in_sector(e, i) && ((float)(e->sector[i].ceiling / 20.0) + 0.5)
				- e->p.pos.z <= 0.25)
		{
			e->z_pos_base = (float)(e->sector[i].ceiling / 20.0) + 0.5;
			break ;
		}
	}
}

static void	condition(t_env *e, int i)
{
	if (e->p.pos.z >= (float)(e->sector[e->p.sector].ceiling / 20.0) - 0.1)
	{
		e->jump_force *= -1.5;
		e->p.pos.z += (float)(e->fps_count.deltaclock / 1000.0) * e->jump_force;
	}
	else
	{
		while (++i < e->current_sector)
		{
			i += (i == e->p.sector ? 1 : 0);
			if (is_in_sector(e, i) && e->p.pos.z >
					((float)(e->sector[i].floor / 20.0) + 0.5 && e->p.pos.z <
					((float)(e->sector[i].ceiling / 20.0) - 0.1)))
				break ;
			else if (is_in_sector(e, i) &&
					((float)(e->sector[i].floor / 20.0) - 0.1) <= e->p.pos.z
					&& e->p.pos.z < ((float)(e->sector[i].ceiling) / 20.0))
			{
				e->jump_force = -1;
				break ;
			}
		}
	}
}

void		p_jump(t_env *e)
{
	int	i;

	i = -1;
	p_movements(e, 95.0, 55.0);
	if (!double_wall(e))
	{
		e->p.mov.x = 0;
		e->p.mov.y = 0;
	}
	e->p.pos.x += e->p.mov.x;
	e->p.pos.y += e->p.mov.y;
	e->p.pos.z += (float)(e->fps_count.deltaclock / 1000.0) * e->jump_force;
	e->jump_force += (float)(e->fps_count.deltaclock / 1000.0) * GRAV_FORCE;
	e->z_pos_base = (float)(e->sector[e->p.sector].floor / 20.0) + 0.5;
	loop(e, i);
	condition(e, i);
	if (e->p.pos.z < e->z_pos_base)
	{
		e->jump_force = 1;
		e->p.pos.z = e->z_pos_base;
		e->p.state = stand;
	}
}
