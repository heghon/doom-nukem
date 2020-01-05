/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:27:43 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/07 03:19:42 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void				point_to_grille(t_point *p)
{
	p->x = p->x % 20 < 10 ? p->x / 20 * 20 : p->x / 20 * 20 + 20;
	p->y = p->y % 20 < 10 ? p->y / 20 * 20 : p->y / 20 * 20 + 20;
}

int					equal_points(t_point *p, t_point *q)
{
	if (p->x == q->x && p->y == q->y)
		return (TRUE);
	return (FALSE);
}

void				brush_color(t_env *env, int color)
{
	env->view.color = color;
}

void				manage_color(t_env *env, int index_wall)
{
	int				color;

	color = WHITE;
	if (env->wall[index_wall].next_sector != -1)
		color = GREEN;
	if (env->editor.select_mode == e_sector)
		if (env->wall[index_wall].sector == env->editor.select[e_sector])
			color = RED;
	if (env->editor.select_mode == e_wall)
		if (env->editor.select[e_wall] == index_wall)
			color = RED;
	brush_color(env, color);
}

void				clear_layer(t_view *view, int layer)
{
	unsigned int	*lay;
	int				i;

	i = -1;
	lay = (unsigned int*)view->layer[layer];
	while (++i < SIDE * SIDE)
		lay[i] = BLACK;
}
