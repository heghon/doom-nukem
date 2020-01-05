/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_fly.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmenant <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:56:31 by bmenant           #+#    #+#             */
/*   Updated: 2019/11/09 17:13:26 by bmenant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	loop1(t_env *e)
{
	int	mult;
	int	i;

	mult = 1;
	i = -1;
	while (++i < e->current_sector)
	{
		i += (i == e->p.sector ? 1 : 0);
		if ((e->keys[SDLK_UP % 42] && is_in_sector(e, i) &&
					((float)(e->sector[i].floor / 20.0) - 0.2) <= e->p.pos.z))
		{
			mult = (e->p.pos.z > (float)(e->sector[i].floor / 20.0) + 0.5
				? 1 : 0);
			break ;
		}
		if ((e->keys[SDLK_DOWN % 42] && is_in_sector(e, i) &&
					((float)(e->sector[i].ceiling / 20.0) + 0.6)
					>= e->p.pos.z))
		{
			mult = (e->p.pos.z < (float)(e->sector[i].ceiling / 20.0) - 0.1
			? 1 : 0);
			break ;
		}
	}
	return (mult);
}

static int	loop2(t_env *e, int mult)
{
	int	i;

	if (e->p.pos.z < (float)(e->sector[e->p.sector].ceiling / 20.0) - 0.35)
		e->p.pos.z += (float)(e->fps_count.deltaclock / 1000.0)
				* e->keys[SDLK_UP % 42] * mult * FLY_FORCE;
	if (e->p.pos.z > (float)(e->sector[e->p.sector].floor / 20.0) + 0.5)
		e->p.pos.z -= (float)(e->fps_count.deltaclock / 1000.0)
				* e->keys[SDLK_DOWN % 42] * mult * FLY_FORCE;
	i = -1;
	while (++i < e->current_sector)
	{
		i += (i == e->p.sector ? 1 : 0);
		if (is_in_sector(e, i))
			break ;
	}
	return (i);
}

void		p_fly(t_env *e)
{
	int	i;

	p_movements(e, 95.0, 95.0);
	if (!(double_wall(e)))
	{
		e->p.mov.x = 0;
		e->p.mov.y = 0;
	}
	e->p.pos.x += e->p.mov.x;
	e->p.pos.y += e->p.mov.y;
	i = loop2(e, loop1(e));
	if (!(e->keys[SDLK_UP % 42] || e->keys[SDLK_DOWN % 42]))
	{
		if (e->p.pos.z < (float)(e->sector[e->p.sector].ceiling / 20.0) - 0.35
			&& e->p.pos.z > (float)(e->sector[e->p.sector].floor / 20.0) + 0.5)
			e->p.pos.z += (i == e->current_sector
					|| e->p.pos.z < ((float)(e->sector[i].floor / 20.0) - 0.35)
					|| e->p.pos.z > (float)(e->sector[i].ceiling / 20.0) + 0.6
					? (float)(e->fps_count.deltaclock / 1000.0)
					* ((float)e->p.fly_mov * 0.01) * FLY_FORCE : 0);
		e->p.fly_mov += (e->p.fly_mov < e->p.old_fly_mov ? -1 : 1);
		e->p.old_fly_mov = (e->p.fly_mov == 20 ? 21 : e->p.old_fly_mov);
		e->p.old_fly_mov = (e->p.fly_mov == -20 ? -21 : e->p.old_fly_mov);
	}
}
