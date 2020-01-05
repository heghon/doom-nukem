/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 19:33:42 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 21:15:36 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "../include/SDL.h"

static int			nb_attr(int mode)
{
	int				nb_attributs;

	if (mode == e_sector)
		nb_attributs = 6;
	else if (mode == e_wall)
		nb_attributs = 1;
	else if (mode == e_object)
		nb_attributs = 5;
	else if (mode == e_character)
		nb_attributs = 7;
	else
		nb_attributs = 0;
	return (nb_attributs);
}

static int			next_attribut(int i, int nb_attributs, int before_next)
{
	if (before_next == 0 && i == 0)
		i = nb_attributs - 1;
	else if (before_next == 0)
		i--;
	if (before_next == 1)
		i = (i + 1) % nb_attributs;
	return (i);
}

void				select_attribut(t_env *env, int before_next)
{
	static	int		i = 0;
	static	int		mode = -1;
	int				changed;
	int				nb_attributs;

	changed = FALSE;
	if (mode != env->editor.select_mode)
	{
		env->editor.attribut[mode][i] = OFF;
		i = 0;
		mode = env->editor.select_mode;
		changed = TRUE;
	}
	nb_attributs = nb_attr(mode);
	env->editor.attribut[mode][i] = OFF;
	if (changed == FALSE)
		i = next_attribut(i, nb_attributs, before_next);
	else
		i = 0;
	env->editor.attribut[mode][i] = ON;
}

static void			update_selected_value(t_env *env, int sign)
{
	update_player(env, sign);
	update_sector(env, sign);
	update_wall(env, sign);
	update_animation(env, sign);
	update_character(env, sign);
	update_object(env, sign);
}

void				update_attribut(t_env *env)
{
	int				sign;

	sign = 0;
	if (env->keys[SDLK_KP_PLUS % 42] == ON)
		sign = 1;
	else if (env->keys[SDLK_KP_MINUS % 42] == ON)
		sign = -1;
	else
	{
		update_selected_value(env, sign);
		return ;
	}
	env->keys[SDLK_KP_PLUS % 42] = OFF;
	env->keys[SDLK_KP_MINUS % 42] = OFF;
	update_selected_value(env, sign);
	re_update_walls(env, env->editor.select[e_sector]);
}
