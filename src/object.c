/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 15:12:01 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:43:37 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			display_ob(t_env *env, t_view *view, t_point pos)
{
	translate(env->editor.direction, &pos);
	plot(view, pos.x, pos.y);
	plot(view, pos.x + 5, pos.y);
	plot(view, pos.x - 5, pos.y);
	plot(view, pos.x, pos.y + 5);
	plot(view, pos.x, pos.y - 5);
	plot(view, pos.x + 5, pos.y + 5);
	plot(view, pos.x - 5, pos.y - 5);
	plot(view, pos.x + 5, pos.y - 5);
	plot(view, pos.x - 5, pos.y + 5);
}

void			display_char(t_env *env, t_view *view, t_point pos)
{
	translate(env->editor.direction, &pos);
	plot(view, pos.x, pos.y);
	plot(view, pos.x + 3, pos.y);
	plot(view, pos.x - 3, pos.y);
	plot(view, pos.x, pos.y + 3);
	plot(view, pos.x, pos.y - 3);
}

void			manage_color_obj(t_env *env, int index_obj)
{
	int			color;

	color = WHITE;
	if (env->editor.select_mode == e_object)
	{
		if (env->editor.select[e_object] == index_obj)
			color = RED;
	}
	brush_color(env, color);
}

void			manage_color_char(t_env *env, int index_character)
{
	int			color;

	color = WHITE;
	if (env->editor.select_mode == e_character)
	{
		if (env->editor.select[e_character] == index_character)
			color = RED;
	}
	brush_color(env, color);
}

void			update_object_extra(t_env *env, int sign)
{
	int			value;
	int			*p_val;
	int			*p_val2;

	if (env->editor.attribut[e_object][3] == ON)
	{
		p_val = &env->object[env->editor.select[e_object]].a.floor;
		p_val2 = &env->object[env->editor.select[e_object]].b.floor;
		value = update_value(p_val, sign, MIN_ALTITUDE, MAX_ALTITUDE);
		*p_val2 = value;
		env->editor.attribut_value = value;
	}
	else if (env->editor.attribut[e_object][4] == ON)
	{
		p_val = &env->object[env->editor.select[e_object]].a.ceiling;
		p_val2 = &env->object[env->editor.select[e_object]].b.ceiling;
		value = update_value(p_val, sign, MIN_ALTITUDE, MAX_ALTITUDE);
		*p_val2 = value;
		env->editor.attribut_value = value;
	}
}
