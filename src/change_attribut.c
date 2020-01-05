/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_attribut.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:58:53 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:31:45 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		update_animation(t_env *env, int sign)
{
	int		value;
	int		*p_val;

	if (env->editor.attribut[e_sector][4] == ON)
	{
		p_val = &env->sector[env->editor.select[e_sector]].animated;
		value = update_value(p_val, sign, 0, 1);
		env->editor.attribut_value = value;
	}
	else if (env->editor.attribut[e_character][4] == ON)
	{
		p_val = &env->character[env->editor.select[e_character]].animated;
		value = update_value(p_val, sign, 0, 1);
		env->editor.attribut_value = value;
	}
	else if (env->editor.attribut[e_object][2] == ON)
	{
		p_val = &env->object[env->editor.select[e_object]].animated;
		value = update_value(p_val, sign, 0, 1);
		env->editor.attribut_value = value;
	}
}

void		update_player(t_env *env, int sign)
{
	int		value;

	if (env->editor.attribut[e_player][0] == ON)
	{
		value = update_value(&env->hud.timer, sign, 0, 1);
		env->editor.attribut_value = value;
	}
}

void		update_sector(t_env *env, int sign)
{
	int		value;
	int		*p_val;

	if (env->editor.attribut[e_sector][0] == ON)
	{
		p_val = &env->sector[env->editor.select[e_sector]].floor;
		value = update_value(p_val, sign, 0, 100);
		env->editor.attribut_value = value;
	}
	else if (env->editor.attribut[e_sector][1] == ON)
	{
		p_val = &env->sector[env->editor.select[e_sector]].ceiling;
		value = update_value(p_val, sign, 0, 100);
		env->editor.attribut_value = value;
	}
	else
	{
		update_sector_tex(env, sign);
		return ;
	}
}

void		update_wall(t_env *env, int sign)
{
	int		value;
	int		*texture;
	int		*next_sector;

	if (env->editor.attribut[e_wall][0] == ON)
	{
		texture = &env->wall[env->editor.select[e_wall]].texture;
		value = update_value(texture, sign, 0, env->card[e_texture]);
		env->editor.attribut_value = value;
	}
	else if (env->editor.attribut[e_wall][1] == ON)
	{
		next_sector = &env->wall[env->editor.select[e_wall]].next_sector;
		value = update_value(next_sector, sign, 0, env->card[e_sector]);
		env->editor.attribut_value = value;
	}
}

void		update_character(t_env *env, int sign)
{
	int		value;
	int		*p_val;

	if (env->editor.attribut[e_character][0] == ON)
	{
		p_val = &env->character[env->editor.select[e_character]].texture[0];
		value = update_value(p_val, sign, 0, env->card[e_texture]);
		env->editor.attribut_value = value;
	}
	else if (env->editor.attribut[e_character][1] == ON)
	{
		p_val = &env->character[env->editor.select[e_character]].texture[1];
		value = update_value(p_val, sign, 0, env->card[e_texture]);
		env->editor.attribut_value = value;
	}
	else if (env->editor.attribut[e_character][2] == ON)
	{
		p_val = &env->character[env->editor.select[e_character]].texture[2];
		value = update_value(p_val, sign, 0, env->card[e_texture]);
		env->editor.attribut_value = value;
	}
	else
		update_character_z(env, sign);
}
