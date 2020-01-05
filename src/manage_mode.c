/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 17:08:34 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/19 08:49:40 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "../include/SDL.h"

void			navigation_editor(t_env *env)
{
	int			moved;

	moved = FALSE;
	if (env->keys[SDLK_KP_2 % 42] && (moved = TRUE))
		env->editor.center.y += DELTA_MOVE_EDITOR;
	if (env->keys[SDLK_KP_4 % 42] && (moved = TRUE))
		env->editor.center.x -= DELTA_MOVE_EDITOR;
	if (env->keys[SDLK_KP_6 % 42] && (moved = TRUE))
		env->editor.center.x += DELTA_MOVE_EDITOR;
	if (env->keys[SDLK_KP_8 % 42] && (moved = TRUE))
		env->editor.center.y -= DELTA_MOVE_EDITOR;
	if (moved == TRUE)
	{
		center_editor(env);
		draw_player(env, YELLOW);
		draw_map(env, WHITE);
		draw_object(env, WHITE);
		draw_character(env, WHITE);
		draw_menu(env);
	}
}

int				manage_editor(t_env *env)
{
	if (env->keys[SDL_BUTTON_LEFT % 42])
	{
		env->current_state[trace] = start_point;
		env->keys[SDL_BUTTON_LEFT % 42] = OFF;
	}
	if (env->keys[SDL_BUTTON_RIGHT % 42])
	{
		if (env->editor.draw_on == OFF)
			add_object(env);
		env->keys[SDL_BUTTON_RIGHT % 42] = OFF;
	}
	update_attribut(env);
	return (SUCCESS);
}

int				manage_game(t_env *env)
{
	if (env->mode == mode_game && env->p.gun && env->keys[SDL_BUTTON_LEFT % 42])
		test_shoot(env);
	SDL_GetRelativeMouseState(&env->mouse.x, &env->mouse.y);
	move_player(env);
	animate_game(env);
	return (SUCCESS);
}

int				manage_start(t_env *env)
{
	static int	f;

	if (f++ == 0)
	{
		init_render(env);
		render(env);
	}
	env->view.main_layer = menu_layer;
	ft_memcpy(env->view.layer[env->view.main_layer],
				env->view.layer[render_layer], SIDE * SIDE * 4);
	start(env);
	if (env->p.current_level != env->p.new_level)
		get_position(env, &env->p);
	return (SUCCESS);
}
