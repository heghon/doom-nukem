/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   framing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 20:23:29 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 23:41:03 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				get_val(t_stream *s, int min, int max)
{
	int			value;

	value = ft_get_nb(s);
	if (value < min)
		return (min);
	else if (value >= max)
		return (max - 1);
	return (value);
}

int				max_val(int type_actor)
{
	if (type_actor == e_object)
		return (NB_OBJECTS);
	if (type_actor == e_sector)
		return (NB_SECTORS);
	if (type_actor == e_wall)
		return (NB_WALLS);
	return (0);
}

int				available_memory(t_env *env, int data)
{
	if ((data == e_character) && env->current_character >= NB_CHARACTERS - 1)
		return (FALSE);
	if ((data == e_object) && env->current_object >= NB_OBJECTS - 1)
		return (FALSE);
	if ((data == e_sector) && env->current_sector >= NB_SECTORS - 1)
		return (FALSE);
	if ((data == e_wall) && env->current_wall >= NB_WALLS - 1)
		return (FALSE);
	if ((data == e_texture) && env->current_texture >= NB_TEXTURES - 1)
		return (FALSE);
	return (TRUE);
}

int				available_action(t_env *env, int actor)
{
	if (env->card_action[actor] >= NB_REACTIONS)
		return (FALSE);
	return (TRUE);
}
