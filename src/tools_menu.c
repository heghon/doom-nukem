/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 23:50:48 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:55:41 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		draw_attr(t_env *env, char *attr[5], t_point *p, t_point *q)
{
	int			i;

	i = -1;
	while (attr[++i])
	{
		if (env->editor.attribut[env->editor.select_mode][i] == ON)
		{
			env->editor.color_text = RED;
			*q = *p;
			q->x += 84;
			q->y += 21;
			update_attribut(env);
			display_value(env, *q, env->editor.attribut_value);
		}
		else
			env->editor.color_text = GREEN;
		display_text(env, *p, attr[i]);
		p->x += 200;
	}
}

static void		start_list(t_env *env)
{
	env->editor.p.x = 20;
	env->editor.p.y = SIDE - 50 - 10;
	env->editor.end.x = env->editor.p.x + 2000;
	env->editor.end.y = env->editor.p.y + 50;
}

static void		draw_list(t_env *env)
{
	static char *a_sect[] = {"floor", "ceiling", "ftex", "ctex", "animated",
													"luminosity", NULL};
	static char *a_wall[] = {"texture", NULL};
	static char *a_charact[] = {"front", "back", "left", "right", "animated",
													"floor", "ceiling", NULL};
	static char *a_object[] = {"texture", "pickable", "animated",
													"floor", "ceiling", NULL};

	start_list(env);
	brush_color(env, BLACK);
	erase_bloc(&env->view, env->editor.p, env->editor.end);
	if (env->editor.select_mode == e_sector)
		draw_attr(env, a_sect, &env->editor.p, &env->editor.q);
	else if (env->editor.select_mode == e_wall)
		draw_attr(env, a_wall, &env->editor.p, &env->editor.q);
	else if (env->editor.select_mode == e_character)
		draw_attr(env, a_charact, &env->editor.p, &env->editor.q);
	else if (env->editor.select_mode == e_object)
		draw_attr(env, a_object, &env->editor.p, &env->editor.q);
	env->editor.p.x = SIDE / 2 + 400;
	env->editor.color_text = DARK_GREEN;
}

static void		draw_type(t_env *env)
{
	int			start;
	t_point		p;
	t_point		q;
	static char *name[] = {"sector", "wall", "object", "character"};

	p.x = SIDE / 2 - 200;
	p.y = SIDE - 150 - 2;
	draw_toolbox(env, p, 80, 500);
	q.x = p.x + 175;
	q.y = p.y + 10;
	env->editor.color_text = YELLOW;
	display_text(env, q, name[env->editor.select_mode]);
	q = p;
	q.x += 150;
	q.y += 50;
	env->editor.color_text = DARK_GREY;
	start = env->card[env->editor.select_mode] == 0 ? 0 : 1;
	display_value(env, q, env->editor.select[env->editor.select_mode] + start);
	q.x += 50;
	display_text(env, q, "of");
	q.x += 250;
	display_value(env, q, env->card[env->editor.select_mode]);
	p.x += 100;
	p.y += 10;
}

void			draw_menu(t_env *env)
{
	draw_type(env);
	draw_list(env);
}
