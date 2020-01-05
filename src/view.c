/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 22:46:26 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/19 07:01:26 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <math.h>

void			plot(t_view *view, int x, int y)
{
	if (x < 0 || y < 0)
		return ;
	if (!((x < SIDE) && (y < SIDE)))
		return ;
	((t_uint*)view->layer[view->main_layer])[x + (SIDE * y)] = view->color;
}

static void		put_pixels(t_view *view, t_point pc, t_point q, int *d)
{
	int			e;
	int			ne;
	int			inc[2];

	inc[0] = (pc.x < q.x ? 1 : -1);
	inc[1] = (pc.y < q.y ? 1 : -1);
	e = (d[0] > d[1] ? d[0] / 2 : -d[1] / 2);
	while (!((pc.x == q.x) && (pc.y == q.y)))
	{
		plot(view, pc.x, pc.y);
		ne = e;
		if (ne > -d[0])
		{
			e -= d[1];
			pc.x += inc[0];
		}
		if (ne < d[1])
		{
			e += d[0];
			pc.y += inc[1];
		}
	}
}

void			draw_line(t_view *v, t_point *start, t_point *end)
{
	int			d[2];

	d[0] = abs(start->x - end->x);
	d[1] = abs(start->y - end->y);
	put_pixels(v, *start, *end, d);
}

void			draw_box(t_env *env, t_point p, int h, int w)
{
	int			i;
	int			j;

	i = p.y - 1;
	while (++i < p.y + h)
	{
		j = p.x - 1;
		while (++j < p.x + w)
		{
			plot(&env->view, j, i);
		}
	}
}

void			draw_toolbox(t_env *env, t_point p, int h, int w)
{
	brush_color(env, BLACK);
	draw_box(env, p, h - 2, w - 2);
	p.x += 63;
	p.y += 10;
}
