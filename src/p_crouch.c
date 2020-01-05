/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_crouch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:46:05 by bmenant           #+#    #+#             */
/*   Updated: 2019/12/09 21:17:06 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	loop(t_env *e)
{
	int	i;

	i = -1;
	while (++i < e->current_sector)
	{
		i += (i == e->p.sector ? 1 : 0);
		if (is_in_sector(e, i)
				&& e->p.pos.z > (float)(e->sector[i].ceiling / 20.0))
		{
			e->z_pos_base = (float)(e->sector[i].ceiling / 20.0) + 0.3;
			if (((float)(e->sector[i].ceiling / 20.0) + 0.3) - e->p.pos.z > 0)
				e->p.pos.z = (float)(e->sector[i].ceiling / 20.0) + 0.3;
			break ;
		}
		else
		{
			e->z_pos_base = (float)(e->sector[e->p.sector].floor / 20.0) + 0.3;
			if (((float)(e->sector[e->p.sector].floor / 20.0) + 0.3)
					- e->p.pos.z > 0 && ((float)(e->sector[e->p.sector].floor
					/ 20.0) + 0.3) - e->p.pos.z < 0.26)
				e->p.pos.z = (float)(e->sector[e->p.sector].floor / 20.0) + 0.3;
		}
	}
}

void		p_crouch(t_env *e)
{
	p_movements(e, 20.0, 20.0);
	if (!double_wall(e))
	{
		e->p.mov.x = 0;
		e->p.mov.y = 0;
	}
	e->p.pos.x += e->p.mov.x;
	e->p.pos.y += e->p.mov.y;
	loop(e);
	if (e->p.pos.z > e->z_pos_base && e->jump_force--)
		e->p.state = jump;
}
