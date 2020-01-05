/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 17:26:29 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/19 08:15:53 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			draw_new_polygon(t_env *env, int select, int color)
{
	int			j;
	int			offset;
	t_wall		*wall;
	t_point		p1;
	t_point		p2;

	j = 0;
	wall = env->wall;
	offset = env->sector[select].start_wall;
	while (j < env->sector[select].num_walls - 1)
	{
		if (color != BLACK)
			manage_color(env, offset + j);
		else
			brush_color(env, BLACK);
		p1 = wall[offset + j].pos;
		p2 = wall[offset + (j + 1) % env->sector[select].num_walls].pos;
		draw_line(&env->view, &p1, &p2);
		j++;
	}
}

void			draw_polygon(t_env *env, int select, int color)
{
	int			j;
	int			offset;
	t_wall		*wall;
	t_point		p1;
	t_point		p2;

	j = 0;
	wall = env->wall;
	offset = env->sector[select].start_wall;
	while (j < env->sector[select].num_walls)
	{
		if (color != BLACK)
			manage_color(env, offset + j);
		else
			brush_color(env, BLACK);
		p1 = wall[offset + j].pos;
		p2 = wall[offset + (j + 1) % env->sector[select].num_walls].pos;
		translate(env->editor.direction, &p1);
		translate(env->editor.direction, &p2);
		draw_line(&env->view, &p1, &p2);
		j++;
	}
}

void			draw_map(t_env *env, int color)
{
	int			i;

	i = 0;
	while (i < env->card[e_sector])
	{
		if (i == env->editor.select[e_sector])
		{
			brush_color(env, RED);
			draw_polygon(env, i++, color);
		}
		else
		{
			brush_color(env, color);
			draw_polygon(env, i++, color);
		}
	}
}

int				draw_object(t_env *env, int color)
{
	int			i;

	i = 0;
	while (i < env->card[e_object])
	{
		if (color != BLACK)
			manage_color_obj(env, i);
		else
			brush_color(env, BLACK);
		display_ob(env, &env->view, env->object[i].pos);
		i++;
	}
	return (SUCCESS);
}

int				draw_character(t_env *env, int color)
{
	int			i;

	i = 0;
	while (i < env->card[e_character])
	{
		if (color != BLACK)
			manage_color_char(env, i);
		else
			brush_color(env, BLACK);
		display_char(env, &env->view, env->character[i].o.pos);
		i++;
	}
	return (SUCCESS);
}
