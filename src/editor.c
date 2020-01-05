/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 11:30:15 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/27 01:12:09 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int					pointer(t_env *env)
{
	if (env->editor.draw_on == TRUE)
	{
		brush_color(env, WHITE);
		draw_line(&env->view, &env->editor.start_line, &env->editor.cursor);
	}
	return (paint);
}

int					create_point(t_env *env)
{
	if (available_memory(env, e_sector) == FALSE)
		return (cursor);
	if (available_memory(env, e_wall) == FALSE)
		return (cursor);
	if (correct_sector(env) == FALSE)
		return (cursor);
	if (correct_wall(env) == FALSE)
		return (cursor);
	env->editor.start_line = env->editor.cursor;
	env->wall[env->current_wall].pos = env->editor.cursor;
	env->editor.old_cursor = env->wall[env->current_wall].pos;
	env->wall[env->current_wall].sector = env->current_sector;
	env->wall[env->current_wall].next_sector = -1;
	if (env->editor.draw_on == OFF)
		return (draw_on);
	else if (equal_points(&env->editor.start_line, &env->editor.start_polygon))
		return (draw_off);
	env->sector[env->current_sector].num_walls++;
	env->current_wall++;
	return (cursor);
}

int					open_polygon(t_env *env)
{
	env->editor.draw_on = ON;
	env->editor.start_polygon = env->editor.start_line;
	env->sector[env->card[e_sector]].start_wall = env->card[e_wall];
	env->sector[env->current_sector].num_walls++;
	env->sector[env->current_sector].ceiling = DEFAULT_CEILING;
	env->sector[env->current_sector].luminosity = 1;
	env->current_wall++;
	return (cursor);
}

int					close_polygon(t_env *env)
{
	env->editor.draw_on = OFF;
	if (correct_polygon(env) == FALSE)
		return (cursor);
	env->card[e_wall] += env->sector[env->current_sector].num_walls;
	env->sector[env->current_sector].index = env->current_sector;
	env->card[e_sector]++;
	move_sector(env);
	re_update_walls(env, env->current_sector);
	env->current_sector++;
	if (connect_sector(env, env->current_sector - 1) == FALSE)
		sector_correction(env, env->current_sector - 1);
	return (cursor);
}

int					draw(t_env *env)
{
	if (env->editor.draw_on)
	{
		env->view.main_layer = editor_layer;
		brush_color(env, WHITE);
		draw_line(&env->view, &env->editor.start_line, &env->editor.cursor);
		draw_new_polygon(env, env->current_sector, WHITE);
	}
	draw_player(env, YELLOW);
	draw_map(env, WHITE);
	draw_object(env, WHITE);
	draw_character(env, WHITE);
	draw_menu(env);
	return (cursor);
}
