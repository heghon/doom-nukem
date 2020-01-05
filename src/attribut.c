/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 03:38:45 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:30:35 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		load_attribute(t_env *env, int type_actor, int n)
{
	if (type_actor == e_object)
	{
		type_actor = e_object + NB_ACTORS * env->object[n].reaction;
		ft_memset(&env->action[type_actor].registre, 0, 4 * NB_REGISTERS);
		object_to_reg(env, n, type_actor);
		return (type_actor);
	}
	else if (type_actor == e_sector)
	{
		type_actor = e_sector + NB_ACTORS * env->sector[n].reaction;
		ft_memset(&env->action[type_actor].registre, 0, 4 * NB_REGISTERS);
		sector_to_reg(env, n, type_actor);
		return (type_actor);
	}
	else if (type_actor == e_character)
	{
		type_actor = e_character + NB_ACTORS * env->character[n].reaction;
		ft_memset(&env->action[type_actor].registre, 0, 4 * NB_REGISTERS);
		character_to_reg(env, n, type_actor);
		return (type_actor);
	}
	return (type_actor);
}

int		save_attribute(t_env *env, int type_actor, int n)
{
	if ((type_actor - e_object) % NB_ACTORS == 0)
		reg_to_object(env, n, type_actor);
	else if ((type_actor - e_sector) % NB_ACTORS == 0)
		reg_to_sector(env, n, type_actor);
	else if ((type_actor - e_character) % NB_ACTORS == 0)
		reg_to_character(env, n, type_actor);
	return (SUCCESS);
}
