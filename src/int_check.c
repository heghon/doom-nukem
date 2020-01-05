/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 19:56:43 by bmenant           #+#    #+#             */
/*   Updated: 2019/12/09 21:06:13 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		ft_mod(t_env *env, int i)
{
	if ((i - env->sector[env->wall[i - 1].sector].num_walls)
			== env->sector[env->wall[i - 1].sector].start_wall)
		return (env->sector[env->wall[i - 1].sector].start_wall);
	return (i);
}

static int		prepare_euc(t_env *e, int i)
{
	int	j;

	j = next_j(e, i, e->wall[i].sector);
	if (left_to_right(&e->p, e->wall[i].previous_pos, e->wall[j].previous_pos))
	{
		e->rend.portal[0].j = e->wall[i];
		e->rend.portal[0].i = e->wall[j];
		e->rend.portal[0].j.previous_pos = e->wall[i].pos;
		e->rend.portal[0].i.previous_pos = e->wall[j].pos;
	}
	e->rend.first_portal = 0;
	e->rend.portal[0].next = e->rend.all;
	return (2);
}

static int		first_loop(t_env *e, int i)
{
	while (++i < e->card[e_wall])
	{
		e->col.p3.x = (float)e->wall[i].pos.x;
		e->col.p3.y = (float)e->wall[i].pos.y;
		e->col.p4.x = (float)e->wall[ft_mod(e, i + 1)].pos.x;
		e->col.p4.y = (float)e->wall[ft_mod(e, i + 1)].pos.y;
		e->bb[i] = bound_box_creation(e->bb[i], e->col.p3, e->col.p4);
		if (hitbox_handler(e, i)
				&& int_seg_seg(e->col.p1, e->col.p2, e->col.p3, e->col.p4))
		{
			if (e->wall[i].next_sector != -1 && e->mode == mode_game
				&& !same_wall(e, e->wall[i].next_sector, e->wall[i].pos))
				return (prepare_euc(e, i));
			if (step_check(e, i))
			{
				e->col.current_wall = i;
				return (collision_point(e));
			}
		}
	}
	return (FALSE);
}

static int		second_loop(t_env *e, int i)
{
	e->col.p3.x = (float)e->wall[i].pos.x;
	e->col.p3.y = (float)e->wall[i].pos.y;
	e->col.p4.x = (float)e->wall[ft_mod(e, i + 1)].pos.x;
	e->col.p4.y = (float)e->wall[ft_mod(e, i + 1)].pos.y;
	e->bb[i] = bound_box_creation(e->bb[i], e->col.p3, e->col.p4);
	if (hitbox_handler(e, i)
			&& int_seg_seg(e->col.p1, e->col.p2, e->col.p3, e->col.p4))
	{
		if (e->wall[i].next_sector != -1 && e->mode == mode_game
			&& !same_wall(e, e->wall[i].next_sector, e->wall[i].pos))
			return (prepare_euc(e, i));
		if (step_check(e, i))
			return (collision_point(e));
	}
	e->col.current_wall = -1;
	return (int_check(e));
}

int				int_check(t_env *e)
{
	int			i;

	i = (e->col.current_wall == -1 ?
			e->sector[e->current_sector].start_wall - 1 : e->col.current_wall);
	if (i == e->sector[e->current_sector].start_wall - 1
		&& ++e->col_recursive < 3)
		return (first_loop(e, i));
	else if (++e->col_recursive < 3)
		return (second_loop(e, i));
	return (FALSE);
}
