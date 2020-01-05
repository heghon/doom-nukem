/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_character.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 05:20:23 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 07:50:07 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		character_to_reg(t_env *env, int n, int type_actor)
{
	if (env->character[n].animated == FALSE)
		return ;
	global_to_reg(env, n, type_actor);
	env->action[type_actor].registre[0] = env->character[n].o.pos.x;
	env->action[type_actor].registre[1] = env->character[n].o.pos.y;
}

void		reg_to_character(t_env *env, int n, int type_actor)
{
	if (env->character[n].animated == FALSE)
		return ;
	reg_to_global(env, n, type_actor);
	env->character[n].o.pos.x = env->action[type_actor].registre[0];
	env->character[n].o.pos.y = env->action[type_actor].registre[1];
}
