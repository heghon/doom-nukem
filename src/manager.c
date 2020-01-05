/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 02:52:49 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 22:59:27 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "../include/SDL.h"

static void		manage_mode(t_env *env)
{
	env->run_mode[mode_editor] = manage_editor;
	env->run_mode[mode_game] = manage_game;
	env->run_mode[mode_start] = manage_start;
}

static void		manage_key(t_env *env)
{
	env->p_keys[SDLK_p % 100] = key_p;
	env->p_keys[SDLK_r % 100] = key_r;
	env->p_keys[SDLK_e % 100] = key_e;
	env->p_keys[SDLK_f % 100] = key_f;
	env->p_keys[SDLK_c % 100] = key_c;
	env->p_keys[SDLK_b % 100] = key_b;
	env->p_keys[SDLK_n % 100] = key_n;
	env->p_keys[SDLK_UP % 100] = key_up;
	env->p_keys[SDLK_DOWN % 100] = key_down;
	env->p_keys[SDLK_LEFT % 100] = key_left;
	env->p_keys[SDLK_RIGHT % 100] = key_right;
	env->p_keys[SDLK_ESCAPE % 100] = key_escape;
	env->p_keys[SDLK_SPACE % 100] = key_space;
	env->p_keys[SDLK_LCTRL % 100] = key_lctrl;
	env->p_keys[SDLK_LALT % 100] = key_alt;
}

static void		manage_controller(t_env *env)
{
	env->p_controller[SDL_KEYDOWN % 10] = key_press;
	env->p_controller[SDL_KEYUP % 10] = key_release;
	env->p_controller[SDL_MOUSEBUTTONDOWN % 10] = mouse_press;
	env->p_controller[SDL_MOUSEBUTTONUP % 10] = mouse_release;
	env->p_controller[SDL_MOUSEMOTION % 10] = mouse_move;
}

static void		manage_automaton(t_env *env)
{
	env->current_state[parser] = file;
	env->pf[parser][file] = init_file;
	env->pf[parser][header] = extract_header;
	env->pf[parser][map] = extract_map;
	env->pf[parser][picture] = extract_picture;
	env->pf[parser][element] = extract_object;
	env->pf[parser][instruction] = extract_code;
	env->pf[parser][sound] = extract_sound;
	env->pf[parser][font] = extract_font;
	env->pf[parser][number] = extract_number;
	env->pf[parser][level] = extract_player;
	env->pf[parser][text] = extract_text;
	env->pf[parser][data] = build_data;
	env->current_state[trace] = cursor;
	env->pf[trace][cursor] = pointer;
	env->pf[trace][start_point] = create_point;
	env->pf[trace][draw_on] = open_polygon;
	env->pf[trace][draw_off] = close_polygon;
	env->pf[trace][paint] = draw;
	env->current_state[rendu] = choose_sector;
	env->pf[rendu][choose_sector] = render;
}

void			manage_program(t_env *env)
{
	manage_mode(env);
	manage_key(env);
	manage_controller(env);
	manage_automaton(env);
	manage_op(env);
}
