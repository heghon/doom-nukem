/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_sector_attributs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 22:17:33 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 12:03:55 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		move_sector(t_env *env)
{
	int		sector;
	int		i;

	sector = env->current_sector;
	i = env->sector[sector].start_wall;
	while (i < env->sector[sector].start_wall + env->sector[sector].num_walls)
	{
		reverse_translate(env->editor.direction, &env->wall[i].pos);
		i++;
	}
}

void		update_sector_tex(t_env *env, int sign)
{
	int		value;
	int		*p_val;
	float	*p_lum;

	value = -1;
	if (env->editor.attribut[e_sector][2] == ON)
	{
		p_val = &env->sector[env->editor.select[e_sector]].tex_f;
		value = update_value(p_val, sign, 0, env->card[e_texture]);
	}
	else if (env->editor.attribut[e_sector][3] == ON)
	{
		p_val = &env->sector[env->editor.select[e_sector]].tex_c;
		value = update_value(p_val, sign, 0, env->card[e_texture]);
	}
	else if (env->editor.attribut[e_sector][5] == ON)
	{
		p_lum = &env->sector[env->editor.select[e_sector]].luminosity;
		value = *p_lum * 100;
		value = update_value(&value, sign, 0, 100);
		value = update_value(&value, sign, 0, 100);
		*p_lum = value / 100.0;
	}
	if (value != -1)
		env->editor.attribut_value = value;
}
