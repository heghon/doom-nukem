/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 11:20:41 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 03:00:36 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			erase_bloc(t_view *view, t_point start, t_point end)
{
	int			temp_x;

	temp_x = start.x;
	while (start.y < end.y)
	{
		start.x = temp_x;
		while (start.x < end.x)
		{
			plot(view, start.x, start.y);
			start.x++;
		}
		start.y++;
	}
}

int				draw_player(t_env *env, int color)
{
	t_point		p[2];
	t_view		*view;
	int			i;

	p[0].x = (int)env->p.pos.x;
	p[0].y = (int)env->p.pos.y;
	view = &env->view;
	i = 4;
	translate(env->editor.direction, &p[0]);
	brush_color(env, color);
	plot(view, p[0].x, p[0].y);
	p[1].x = p[0].x + env->p.dir.x * 20;
	p[1].y = p[0].y + env->p.dir.y * 20;
	draw_line(&env->view, &p[0], &p[1]);
	while (i--)
	{
		plot(view, p[0].x + i, p[0].y);
		plot(view, p[0].x - i, p[0].y);
		plot(view, p[0].x, p[0].y + i);
		plot(view, p[0].x, p[0].y - i);
	}
	return (SUCCESS);
}
