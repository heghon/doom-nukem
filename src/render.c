/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 00:54:05 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/09 21:19:34 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	display_cross(t_env *env)
{
	int x;
	int y;
	int color;
	int layer;

	layer = env->view.current_layer;
	color = env->view.color;
	env->view.color = 0x444444;
	env->view.current_layer = render_layer;
	x = SIDE / 2;
	y = SIDE / 2 - 15;
	while (++y < SIDE / 2 + 15)
		plot(&env->view, x, y);
	y = SIDE / 2;
	x = SIDE / 2 - 15;
	while (++x < SIDE / 2 + 15)
		plot(&env->view, x, y);
	env->view.color = color;
	env->view.current_layer = layer;
}

void	look_around(t_env *env)
{
	int				x;
	int				y;
	float			tmp;
	float			modif;
	int				i;

	x = env->mouse.x > SIDE / 3 ? SIDE / 3 : env->mouse.x;
	x = x < -SIDE / 3 ? -SIDE / 3 : x;
	y = env->mouse.y > SIDE / 3 ? SIDE / 3 : env->mouse.y;
	y = y < -SIDE / 3 ? -SIDE / 3 : y;
	i = 2;
	modif = 0;
	while (abs(y) > (SIDE / 300) * i++ && i < SIDE / 2)
		modif += y > 0 ? 2 : -2;
	env->p.cam -= modif / (SIDE);
	env->p.cam = (env->p.cam < 0 ? 0 : env->p.cam);
	env->p.cam = (env->p.cam > 1 ? 1 : env->p.cam);
	i = 1;
	modif = 0;
	while (abs(x) > (SIDE / 200) * i++ && i < SIDE / 2)
		modif += 0.005;
	modif = x < 0 ? modif : -modif;
	tmp = env->p.dir.x;
	env->p.dir.x = env->p.dir.x * cos(-modif) - env->p.dir.y * sin(-modif);
	env->p.dir.y = tmp * sin(-modif) + env->p.dir.y * cos(-modif);
}
