/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 08:26:46 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 08:39:03 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "../include/SDL.h"

void		init_automaton(t_env *env)
{
	env->activated[parser] = ON;
	env->activated[trace] = OFF;
	env->activated[rendu] = OFF;
	env->current_state[parser] = file;
	env->iter_max[parser] = 1;
	env->iter_max[trace] = 1;
	env->iter_max[rendu] = 1;
}

void		init_hud(t_env *env)
{
	int i;

	i = -1;
	env->hud.compass = OFF;
	env->hud.timer = OFF;
	env->hud.nb_inventory = 0;
	env->hud.inventory[0] = -1;
	env->hud.inventory[1] = -1;
	env->hud.inventory[2] = -1;
	env->hud.inventory[3] = -1;
	env->hud.inventory[4] = -1;
	env->hud.inventory[5] = -1;
	env->hud.inventory[6] = -1;
	env->hud.inventory[7] = -1;
	while (++i < 8)
		env->hud.bu[i] = env->hud.inventory[i];
	env->s_font = SIDE / 400 >= 1 ? SIDE / 400 : 1;
	env->current_sentence = 0;
}

void		init_player(t_env *env)
{
	env->p.dir.x = 1;
	env->p.current_level = 0;
	env->p.new_level = 0;
	env->p.state = stand;
	env->p.cam = 0.5;
	env->p.fly_mov = -10;
	env->p.old_fly_mov = -11;
	env->p.total_time = 0;
	env->p.timer = 0;
	env->p.sprint = OFF;
	env->p.wings = OFF;
	env->p.gun = OFF;
}

void		init_fps(t_env *env)
{
	env->col.current_wall = -1;
	env->fps_count.startclock = 0;
	env->fps_count.deltaclock = 0;
	env->fps_count.current_fps = 0;
	env->fps_count.startclock = SDL_GetTicks();
}
