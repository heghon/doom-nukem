/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 23:21:03 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 06:26:50 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		translate(t_point direction, t_point *p)
{
	p->x += direction.x;
	p->y += direction.y;
}

void		reverse_translate(t_point direction, t_point *p)
{
	p->x -= direction.x;
	p->y -= direction.y;
}

void		update_translation(t_env *env, t_point c)
{
	t_point old;
	t_point new;

	env->editor.center = c;
	old = env->editor.direction;
	new.x = SIDE / 2 - c.x;
	new.y = SIDE / 2 - c.y;
	if (equal_points(&old, &new) == FALSE)
	{
		draw_player(env, BLACK);
		draw_map(env, BLACK);
		draw_object(env, BLACK);
		draw_character(env, BLACK);
	}
	env->editor.direction = new;
}

void		center_editor(t_env *env)
{
	t_point	c;

	c.x = env->editor.center.x;
	c.y = env->editor.center.y;
	update_translation(env, c);
}

void		centering(t_env *env)
{
	t_point	c;
	int		index;

	c.x = env->editor.center.x;
	c.y = env->editor.center.y;
	if (env->editor.select_mode == e_sector && env->card[e_sector])
	{
		index = env->sector[env->editor.select[e_sector]].start_wall;
		c = env->wall[index].pos;
	}
	else if (env->editor.select_mode == e_wall && env->card[e_wall])
	{
		c = env->wall[env->editor.select[e_wall]].pos;
	}
	else if (env->editor.select_mode == e_object && env->card[e_object])
	{
		index = env->editor.select[e_object];
		c = env->object[index].pos;
	}
	else if (env->editor.select_mode == e_character && env->card[e_character])
	{
		index = env->editor.select[e_character];
		c = env->character[index].o.pos;
	}
	update_translation(env, c);
}
