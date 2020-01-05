/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_efrp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/31 17:59:17 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 22:08:23 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "../include/SDL.h"

int		key_e(t_env *env)
{
	if (env->option.editor == FALSE)
		return (SUCCESS);
	env->activated[trace] = ON;
	env->activated[rendu] = OFF;
	env->mode = mode_editor;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	env->current_state[rendu] = choose_sector;
	env->view.main_layer = editor_layer;
	key_c(env);
	return (SUCCESS);
}

int		key_c(t_env *env)
{
	if (env->mode == mode_editor)
	{
		env->editor.draw_on = OFF;
		env->current_wall = env->card[e_wall];
		env->sector[env->card[e_sector]].num_walls = 0;
		clear_layer(&env->view, editor_layer);
		draw_map(env, WHITE);
	}
	return (SUCCESS);
}

int		key_r(t_env *env)
{
	if (env->mode == mode_game || (env->mode == mode_start
			&& env->keys[SDLK_KP_ENTER % 42] == OFF))
		return (SUCCESS);
	env->activated[trace] = OFF;
	env->activated[rendu] = ON;
	env->mode = mode_game;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	struct_direction(env);
	init_render(env);
	env->current_state[rendu] = choose_sector;
	env->view.main_layer = render_layer;
	clear_layer(&env->view, render_layer);
	return (SUCCESS);
}

int		key_p(t_env *env)
{
	env->editor.center.x = env->p.pos.x;
	env->editor.center.y = env->p.pos.y;
	center_editor(env);
	return (SUCCESS);
}

int		key_f(t_env *env)
{
	if (env->mode == mode_editor)
		save_file(env);
	return (SUCCESS);
}
