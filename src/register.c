/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 04:17:05 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 21:01:58 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		object_to_reg(t_env *env, int n, int type_actor)
{
	if (env->object[n].animated == FALSE)
		return ;
	global_to_reg(env, n, type_actor);
	env->action[type_actor].registre[0] = env->object[n].pos.x;
	env->action[type_actor].registre[1] = env->object[n].pos.y;
	env->action[type_actor].registre[2] = env->object[n].color;
	env->action[type_actor].registre[6] = env->object[n].reaction;
	env->action[type_actor].registre[7] = n;
	env->action[type_actor].registre[8] = env->object[n].a.floor;
	env->action[type_actor].registre[9] = env->object[n].a.ceiling;
}

void		sector_to_reg(t_env *env, int n, int type_actor)
{
	if (env->sector[n].animated == FALSE)
		return ;
	global_to_reg(env, n, type_actor);
	env->action[type_actor].registre[4] = env->sector[n].floor;
	env->action[type_actor].registre[5] = env->sector[n].ceiling;
	env->action[type_actor].registre[6] = env->sector[n].reaction;
	env->action[type_actor].registre[7] = env->sector[n].count;
	env->action[type_actor].registre[8] = env->sector[n].luminosity * 100;
	env->action[type_actor].registre[12] = n;
}

void		reg_to_object(t_env *env, int n, int type_actor)
{
	if (env->object[n].animated == FALSE)
		return ;
	reg_to_global(env, n, type_actor);
	env->object[n].pos.x = env->action[type_actor].registre[0];
	env->object[n].pos.y = env->action[type_actor].registre[1];
	env->object[n].color = env->action[type_actor].registre[2];
	env->object[n].alert = env->action[type_actor].registre[15];
	env->object[n].reaction = abs(env->action[type_actor].registre[6]);
	if (env->object[n].reaction >= NB_REACTIONS)
		env->object[n].reaction = 0;
	env->object[n].a.floor = env->action[type_actor].registre[8];
	env->object[n].a.ceiling = env->action[type_actor].registre[9];
	env->object[n].b.floor = env->action[type_actor].registre[8];
	env->object[n].b.ceiling = env->action[type_actor].registre[9];
}

void		reg_to_sector(t_env *env, int n, int type_actor)
{
	int		i;

	if (env->sector[n].animated == FALSE)
		return ;
	reg_to_global(env, n, type_actor);
	i = env->sector[n].start_wall;
	while (i < env->sector[n].num_walls + env->sector[n].start_wall)
	{
		env->wall[i].pos.x += env->action[type_actor].registre[0];
		env->wall[i].pos.y += env->action[type_actor].registre[1];
		env->wall[i].floor += env->action[type_actor].registre[2];
		env->wall[i].ceiling += env->action[type_actor].registre[3];
		i++;
	}
	env->sector[n].floor = env->action[type_actor].registre[4];
	env->sector[n].ceiling = env->action[type_actor].registre[5];
	env->sector[n].reaction = abs(env->action[type_actor].registre[6]);
	if (env->sector[n].reaction >= NB_REACTIONS)
		env->sector[n].reaction = 0;
	env->sector[n].count = env->action[type_actor].registre[7];
	env->sector[n].luminosity = env->action[type_actor].registre[8] / 100.0;
	re_update_walls(env, n);
}
