/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 23:57:26 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 20:44:21 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "../include/SDL.h"

int		filter_event(void *data, SDL_Event *event)
{
	(void)data;
	if (event->type == SDL_KEYDOWN || event->type == SDL_KEYUP)
		return (TRUE);
	if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
		return (TRUE);
	if (event->type == SDL_MOUSEMOTION)
		return (TRUE);
	if (event->type == SDL_QUIT)
		return (TRUE);
	return (FALSE);
}

int		filter_keys(int k)
{
	if (k == SDLK_KP_2 || k == SDLK_KP_4 || k == SDLK_KP_6 || k == SDLK_KP_8)
		return (TRUE);
	if (k == SDLK_w || k == SDLK_a || k == SDLK_s || k == SDLK_d)
		return (TRUE);
	if (k == SDLK_LEFT || k == SDLK_RIGHT || k == SDLK_UP || k == SDLK_DOWN)
		return (TRUE);
	if (k == SDLK_LCTRL || k == SDLK_LALT || k == SDLK_LSHIFT)
		return (TRUE);
	if (k == SDLK_KP_PLUS || k == SDLK_KP_MINUS)
		return (TRUE);
	if (k == SDLK_KP_ENTER)
		return (TRUE);
	return (FALSE);
}

int		filter_pkeys(int k)
{
	if (k == SDLK_p || k == SDLK_r || k == SDLK_e || k == SDLK_f)
		return (TRUE);
	if (k == SDLK_c || k == SDLK_x)
		return (TRUE);
	if (k == SDLK_b || k == SDLK_n)
		return (TRUE);
	if (k == SDLK_UP || k == SDLK_DOWN || k == SDLK_LEFT || k == SDLK_RIGHT)
		return (TRUE);
	if (k == SDLK_ESCAPE || k == SDLK_SPACE)
		return (TRUE);
	if (k == SDLK_LCTRL || k == SDLK_LALT || k == SDLK_LSHIFT)
		return (TRUE);
	return (FALSE);
}
