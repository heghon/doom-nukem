/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 20:21:10 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/10 17:36:27 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "../include/SDL.h"

void		p_movements(t_env *e, float mult, float div)
{
	e->p.mov.x = 0;
	e->p.mov.y = 0;
	e->p.mov.x += (float)SPEED * e->p.dir.x * e->keys[SDLK_w % 42]
	* (float)(e->fps_count.deltaclock / 1000.0) * mult * (int)e->col.k;
	e->p.mov.y += (float)SPEED * e->p.dir.y * e->keys[SDLK_w % 42]
	* (float)(e->fps_count.deltaclock / 1000.0) * mult * (int)e->col.k;
	e->p.mov.x -= (float)SPEED * e->p.dir.x * e->keys[SDLK_s % 42]
	* (float)(e->fps_count.deltaclock / 1000.0) * div * (int)e->col.k;
	e->p.mov.y -= (float)SPEED * e->p.dir.y * e->keys[SDLK_s % 42]
	* (float)(e->fps_count.deltaclock / 1000.0) * div * (int)e->col.k;
	e->p.mov.x += (float)SPEED * e->p.dir.y * e->keys[SDLK_a % 42]
	* (float)(e->fps_count.deltaclock / 1000.0) * div * (int)e->col.k;
	e->p.mov.y -= (float)SPEED * e->p.dir.x * e->keys[SDLK_a % 42]
	* (float)(e->fps_count.deltaclock / 1000.0) * div * (int)e->col.k;
	e->p.mov.x -= (float)SPEED * e->p.dir.y * e->keys[SDLK_d % 42]
	* (float)(e->fps_count.deltaclock / 1000.0) * div * (int)e->col.k;
	e->p.mov.y += (float)SPEED * e->p.dir.x * e->keys[SDLK_d % 42]
	* (float)(e->fps_count.deltaclock / 1000.0) * div * (int)e->col.k;
	if (e->keys[SDLK_LSHIFT % 42] && e->p.sprint != 0)
	{
		e->p.mov.x *= 2.0;
		e->p.mov.y *= 2.0;
	}
	e->p.mov.x += e->col.x;
	e->p.mov.y += e->col.y;
}

void		update_position(t_env *e)
{
	if (e->p.current_level != e->p.new_level)
	{
		get_position(e, &e->p);
		return ;
	}
	e->col.k *= (isnan(e->col.k) ? 0 : 1);
	if (e->p.sector == -1 || e->sector[e->p.sector].luminosity == 0)
	{
		e->p.pos.x = e->p.old_pos.x;
		e->p.pos.y = e->p.old_pos.y;
		e->p.pos.z = e->p.old_pos.z;
	}
	e->p.old_pos.x = e->p.pos.x;
	e->p.old_pos.y = e->p.pos.y;
	e->p.old_pos.z = e->p.pos.z;
	if (e->p.state == crouch)
		p_crouch(e);
	if (e->p.state == stand)
		p_stand(e);
	if (e->p.state == jump)
		p_jump(e);
	if (e->p.state == fly)
		p_fly(e);
}
