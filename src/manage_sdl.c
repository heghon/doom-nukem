/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sdl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:36:03 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/19 08:50:55 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <stdlib.h>
#include "../include/SDL.h"

static int			init_layer(t_env *env)
{
	env->view.layer[editor_layer] = malloc(sizeof(char) * SIDE * SIDE * 4);
	env->view.layer[render_layer] = malloc(sizeof(char) * SIDE * SIDE * 4);
	env->view.layer[menu_layer] = malloc(sizeof(char) * SIDE * SIDE * 4);
	return (SUCCESS);
}

int					init_view(t_env *env)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (ERROR);
	env->win = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SIDE, SIDE, SDL_WINDOW_SHOWN);
	if (env->win == NULL)
		return (ERROR);
	env->render = SDL_CreateRenderer(env->win, -1,
			SDL_RENDERER_SOFTWARE);
	if (env->render == NULL)
		return (ERROR);
	env->screen = SDL_CreateTexture(env->render,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			SIDE, SIDE);
	if (env->screen == NULL)
		return (ERROR);
	SDL_SetEventFilter(filter_event, NULL);
	return (init_layer(env));
}

int					listen_event(t_env *env, SDL_Event *event)
{
	int				ret;

	ret = SUCCESS;
	while (SDL_PollEvent(event))
	{
		if (env->event.type == SDL_QUIT)
			return (FALSE);
		else if (env->p_controller[event->type % 10])
			ret = env->p_controller[event->type % 10](env);
		if (ret == END)
			return (FALSE);
	}
	return (TRUE);
}

int					refresh_screen(t_env *env)
{
	int				l;

	l = env->view.main_layer;
	SDL_UpdateTexture(env->screen, NULL, env->view.layer[l], SIDE * 4);
	SDL_RenderCopy(env->render, env->screen, NULL, NULL);
	SDL_RenderPresent(env->render);
	return (SUCCESS);
}
