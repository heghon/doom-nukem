/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 23:56:49 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 22:57:43 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			screenshoot(t_env *env)
{
	int layer;

	layer = env->view.main_layer;
	env->view.main_layer = render_layer;
	env->pf[rendu][env->current_state[rendu]](env);
	env->view.main_layer = layer;
}

void			get_position(t_env *env, t_player *p)
{
	p->current_level = p->new_level;
	if (env->nb_level <= 0 || p->new_level >= env->nb_level)
	{
		p->pos.x = 0;
		p->pos.y = 0;
		p->pos.z = 1;
	}
	else
	{
		p->pos.x = p->levels[p->current_level].x;
		p->pos.y = p->levels[p->current_level].y;
		p->pos.z = p->levels[p->current_level].z / 20.0 + 0.5;
	}
	p->dir.x = 1;
	p->dir.y = 0;
	if (env->mode == mode_start)
		screenshoot(env);
}

int				run_programme(t_env *env)
{
	int			i;
	int			j;
	static int	ss;

	if (env->activated[parser] == OFF && ss++ == 0)
		get_position(env, &env->p);
	i = -1;
	while (++i < NB_AUTOMATES)
	{
		j = -1;
		if (env->activated[i] == ON)
			while (++j < env->iter_max[i])
				env->current_state[i] = env->pf[i][env->current_state[i]](env);
	}
	if (env->activated[parser] == OFF)
		env->run_mode[env->mode](env);
	return (SUCCESS);
}

void			run_game(t_env *env)
{
	while (listen_event(env, &env->event))
	{
		run_programme(env);
		refresh_screen(env);
	}
}

void			init_game(t_env *env)
{
	init_automaton(env);
	init_render(env);
	init_hud(env);
	init_fps(env);
	init_player(env);
	bound_box_p(env);
	key_p(env);
	env->editor.color_text = WHITE;
	env->view.main_layer = menu_layer;
	env->editor.select_mode = e_sector;
	env->mode = mode_start;
	env->option.editor = OFF;
	env->option.thread = ON;
}
