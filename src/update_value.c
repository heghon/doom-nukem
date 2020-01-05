/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 22:04:35 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 03:00:12 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	in_interval(int value, int min, int max, int sign)
{
	if ((sign == -1 && value - 1 < min))
		return (FALSE);
	if ((sign == 1 && value + 1 > max))
		return (FALSE);
	return (TRUE);
}

static int	renew(int *value, int sign)
{
	*value = *value + 1 * sign;
	return (TRUE);
}

int			update_value(int *val, int sign, int min, int max)
{
	if (in_interval(*val, min, max, sign) == TRUE)
		renew(val, sign);
	return (*val);
}

void		update_object(t_env *env, int sign)
{
	int		value;
	int		*p_val;
	int		*p_val2;

	if (env->editor.attribut[e_object][0] == ON)
	{
		p_val = &env->object[env->editor.select[e_object]].a.texture;
		p_val2 = &env->object[env->editor.select[e_object]].b.texture;
		value = update_value(p_val, sign, 0, env->card[e_texture]);
		*p_val2 = value;
		env->editor.attribut_value = value;
	}
	else if (env->editor.attribut[e_object][1] == ON)
	{
		p_val = &env->object[env->editor.select[e_object]].pickable;
		value = update_value(p_val, sign, 0, 2);
		env->editor.attribut_value = value;
	}
	else
		update_object_extra(env, sign);
}

void		update_character_z(t_env *env, int sign)
{
	int		value;
	int		*p_val;

	if (env->editor.attribut[e_character][3] == ON)
	{
		p_val = &env->character[env->editor.select[e_character]].texture[3];
		value = update_value(p_val, sign, 0, env->card[e_texture]);
		env->editor.attribut_value = value;
	}
	else if (env->editor.attribut[e_character][4] == ON)
	{
		p_val = &env->character[env->editor.select[e_character]].animated;
		value = update_value(p_val, sign, 0, 1);
		env->editor.attribut_value = value;
	}
	else
		update_character_extra(env, sign);
}
