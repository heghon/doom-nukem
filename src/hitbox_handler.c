/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 16:06:45 by bmenant           #+#    #+#             */
/*   Updated: 2019/12/09 20:56:14 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <math.h>

void		bound_box_p(t_env *e)
{
	e->bb_player.min.x = e->p.pos.x - 10;
	e->bb_player.max.x = e->p.pos.x + 10;
	e->bb_player.min.y = e->p.pos.y - 10;
	e->bb_player.max.y = e->p.pos.y + 10;
}

t_bound_box	bound_box_creation(t_bound_box bb, t_float a, t_float b)
{
	bb.min.x = fmin(a.x, b.x) - 10;
	bb.max.x = fmax(a.x, b.x) + 10;
	bb.min.y = fmin(a.y, b.y) - 10;
	bb.max.y = fmax(a.y, b.y) + 10;
	return (bb);
}

int			hitbox_handler(t_env *e, int i)
{
	t_bound_box a;
	t_bound_box b;

	b = e->bb_player;
	a = e->bb[i];
	if ((b.min.x >= a.max.x) || (b.max.x <= a.min.x)
			|| (b.min.y >= a.max.y) || (b.max.y <= a.min.y))
		return (FALSE);
	return (TRUE);
}
