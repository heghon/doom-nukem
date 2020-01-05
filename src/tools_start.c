/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseneca <sseneca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 06:01:47 by sseneca           #+#    #+#             */
/*   Updated: 2019/12/09 23:49:19 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		change_luminosity(t_sector *s)
{
	if (s->luminosity >= 1.0)
		s->luminosity -= 0.011;
	else if (s->luminosity < 0.99)
		s->luminosity += 0.011;
}

void		reverse(unsigned int *n)
{
	if (*n == 0)
		*n = 1;
	else if (*n == 1)
		*n = 0;
}

void		manage_level(t_player *p, int n)
{
	if (p->new_level < n - 1)
		p->new_level++;
	else
		p->new_level = 0;
}

static void	display_edge(t_env *env, t_point p[4])
{
	int			i;

	i = -1;
	while (++i < 6)
	{
		env->view.color -= 0x222222;
		draw_line(&env->view, &p[0], &p[1]);
		draw_line(&env->view, &p[1], &p[3]);
		draw_line(&env->view, &p[2], &p[0]);
		draw_line(&env->view, &p[3], &p[2]);
		p[0].x--;
		p[0].y++;
		p[1].x++;
		p[1].y++;
		p[2].x--;
		p[2].y--;
		p[3].x++;
		p[3].y--;
	}
}

void		display_box(t_env *env, t_point p[4], int height, int here)
{
	int			color;

	color = env->view.color;
	env->view.color = here == 0 ? 0xDDDDDD : 0xFFFFFF;
	p[2] = p[0];
	p[3] = p[1];
	while (p[0].y < height + (HEIGHT_FONT * env->s_font * 2))
	{
		draw_line(&env->view, &p[0], &p[1]);
		p[0].y++;
		p[1].y++;
	}
	display_edge(env, p);
	color = env->view.color;
}
