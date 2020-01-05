/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseneca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 05:19:53 by sseneca           #+#    #+#             */
/*   Updated: 2019/12/01 05:20:21 by sseneca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "../include/SDL.h"

static void	draw_icon(t_env *env, t_texture *tex, t_point s, t_point start)
{
	int	i;
	int	j;
	int	h;
	int	w;

	i = -1;
	while (++i < s.y)
	{
		j = -1;
		h = (i / (float)s.y) * tex->h;
		while (++j < s.x)
		{
			w = (j / (float)s.x) * tex->w;
			env->view.color = color_tex(tex->picture, 4
					* (h * tex->w + w),
					env->sector[env->p.sector].luminosity);
			if (env->view.color != 0)
				plot(&env->view, start.x + j, start.y + i);
		}
	}
}

static void	display_icon(t_env *env, t_point middle, t_texture *tex)
{
	t_point	start;
	t_point	size;

	if (tex->h <= tex->w)
		start.x = SIDE - (SIDE / 9);
	else
		start.x = SIDE - (SIDE / 18) - ((SIDE / 18)
				* (tex->w / (float)tex->h));
	if (tex->w <= tex->h)
		start.y = middle.y + (SIDE / 8 - (SIDE / 9));
	else
		start.y = middle.y + (SIDE / 8 - (SIDE / 9
					* (0.5 + (0.5 * (tex->h / (float)tex->w)))));
	size.x = ((SIDE - (SIDE / 17)) - start.x) * 2;
	size.y = (((middle.y + (SIDE / 8)) - (SIDE / 17)) - start.y) * 2;
	draw_icon(env, tex, size, start);
}

void		display_inventory(t_env *env, int nb, int tex, float l)
{
	t_point	p[2];
	t_point	middle;
	int		i;

	middle.x = SIDE - (SIDE / 8);
	middle.y = SIDE - (SIDE / 8 * (nb + 1));
	p[0].x = SIDE - (SIDE / 8);
	p[0].y = SIDE - ((SIDE / 8) * nb);
	p[1].x = SIDE;
	p[1].y = SIDE - (SIDE / 8 * (nb + 1));
	draw_line(&env->view, &middle, &p[0]);
	draw_line(&env->view, &middle, &p[1]);
	i = 0;
	while (i++ < 9)
	{
		middle.x++;
		middle.y++;
		p[0].x++;
		p[1].y++;
		draw_line(&env->view, &middle, &p[0]);
		draw_line(&env->view, &middle, &p[1]);
		env->view.color = adapt_luminosity(0x111111 * (i - 1), l);
	}
	middle.y -= 8;
	display_icon(env, middle, &env->texture[tex]);
}
