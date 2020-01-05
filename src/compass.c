/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseneca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 05:19:31 by sseneca           #+#    #+#             */
/*   Updated: 2019/12/01 05:19:33 by sseneca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "../include/SDL.h"

static void	display_border(t_env *env, t_point middle, int max, float l)
{
	int		i;
	t_point	point[4];

	i = -1;
	point[0].y = middle.y;
	point[1].y = middle.y;
	point[2].x = middle.x;
	point[3].x = middle.x;
	while (++i < 9)
	{
		env->view.color = adapt_luminosity((i + 1) * 0x111111, l);
		point[0].x = middle.x + max / 2 + i;
		point[1].x = middle.x - max / 2 - i;
		point[2].y = middle.y - max / 2 - i;
		point[3].y = middle.y + max / 2 + i;
		draw_line(&env->view, &point[0], &point[3]);
		draw_line(&env->view, &point[1], &point[2]);
		draw_line(&env->view, &point[2], &point[0]);
		draw_line(&env->view, &point[3], &point[1]);
	}
}

static void	display_needle(t_env *env, t_point middle, int max, float l)
{
	t_point p[2];
	int		i;
	int		thickness;

	p[0].x = middle.x;
	p[0].y = middle.y;
	p[1].x = middle.x - env->p.dir.x * -max * 0.33;
	p[1].y = middle.y + env->p.dir.y * max * 0.33;
	i = -8;
	thickness = 8;
	env->view.color = adapt_luminosity(0x990000, l);
	while (++i < thickness)
	{
		p[0].y = middle.y + i;
		draw_line(&env->view, &p[0], &p[1]);
		p[0].y -= i;
		p[0].x = middle.x + i;
		draw_line(&env->view, &p[0], &p[1]);
		p[0].x -= i;
	}
	display_border(env, middle, max, l);
}

static void	display_nwes(t_env *env, t_point middle, int max, float l)
{
	t_point	p;
	int		color;

	color = env->editor.color_text;
	env->editor.color_text = adapt_luminosity(0x333333, l);
	p.x = middle.x - ((WIDTH_FONT * env->s_font) / 2 - 1);
	p.y = middle.y - (max / 2) + (HEIGHT_FONT * env->s_font / 2 + 1);
	display_text(env, p, "n");
	p.y = middle.y + (max / 2) - (HEIGHT_FONT * env->s_font
			+ (HEIGHT_FONT * env->s_font / 2));
	display_text(env, p, "s");
	p.y = middle.y - ((WIDTH_FONT * env->s_font) / 2 - 1);
	p.x = middle.x - (max / 2) + (HEIGHT_FONT * env->s_font / 2 + 1);
	display_text(env, p, "w");
	p.x = middle.x + (max / 2) - (HEIGHT_FONT * env->s_font
			+ (HEIGHT_FONT * env->s_font / 2));
	display_text(env, p, "e");
	env->editor.color_text = color;
	display_needle(env, middle, max, l);
}

void		display_compass(t_env *env, float l)
{
	t_point	p[2];
	t_point	middle;
	int		max;
	int		i;
	int		c;

	middle.x = (SIDE / 10);
	middle.y = SIDE - (SIDE / 10);
	max = SIDE > SIDE ? SIDE / 7 : SIDE / 7;
	max = max % 2 == 0 ? max + 1 : max;
	p[0] = middle;
	p[0].y -= (max / 2);
	p[1] = p[0];
	i = -1;
	c = 1;
	while (++i < max)
	{
		draw_line(&env->view, &p[0], &p[1]);
		c = p[1].x - p[0].x > max - 3 || c == -1 ? -1 : 1;
		p[0].y++;
		p[1].y++;
		p[0].x -= c;
		p[1].x += c;
	}
	display_nwes(env, middle, max, l);
}
