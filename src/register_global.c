/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_global.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:19:14 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 23:47:14 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	save_precision(t_env *env, int n, int type_actor)
{
	float	save_x;
	float	save_y;
	float	save_z;

	(void)n;
	save_x = env->p.pos.x - (int)env->p.pos.x;
	save_y = env->p.pos.y - (int)env->p.pos.y;
	save_z = env->p.pos.z - (int)env->p.pos.z;
	env->action[type_actor].registre[139] = save_x * PRECISION;
	env->action[type_actor].registre[140] = save_y * PRECISION;
	env->action[type_actor].registre[141] = save_z * PRECISION;
}

static void	recover_precision(t_env *env, int n, int type_actor)
{
	float	recover_x;
	float	recover_y;
	float	recover_z;

	(void)n;
	recover_x = (float)env->action[type_actor].registre[139];
	recover_y = (float)env->action[type_actor].registre[140];
	recover_z = (float)env->action[type_actor].registre[141];
	env->p.pos.x += recover_x / PRECISION;
	env->p.pos.y += recover_y / PRECISION;
	env->p.pos.z += recover_z / PRECISION;
}

void		global_to_reg(t_env *env, int n, int type_actor)
{
	save_precision(env, n, type_actor);
	env->action[type_actor].registre[118] = env->p.new_level;
	env->action[type_actor].registre[119] = env->p.sector;
	env->action[type_actor].registre[120] = env->p.pos.x;
	env->action[type_actor].registre[121] = env->p.pos.y;
	env->action[type_actor].registre[122] = env->p.pos.z;
	env->action[type_actor].registre[123] = env->hud.inventory[0];
	env->action[type_actor].registre[124] = env->hud.inventory[1];
	env->action[type_actor].registre[125] = env->hud.inventory[2];
	env->action[type_actor].registre[126] = env->hud.inventory[3];
	env->action[type_actor].registre[127] = env->hud.inventory[4];
	env->action[type_actor].registre[128] = env->hud.inventory[5];
	env->action[type_actor].registre[129] = env->hud.inventory[6];
	env->action[type_actor].registre[130] = env->hud.inventory[7];
	env->action[type_actor].registre[131] = env->current_sentence;
	env->action[type_actor].registre[132] = env->hud.compass;
	env->action[type_actor].registre[133] = env->hud.timer;
}

static void	update_hud(t_env *env, int n, int type_actor)
{
	(void)n;
	env->hud.compass = env->action[type_actor].registre[132];
	env->hud.timer = env->action[type_actor].registre[133];
	env->hud.inventory[0] = env->action[type_actor].registre[123];
	env->hud.inventory[1] = env->action[type_actor].registre[124];
	env->hud.inventory[2] = env->action[type_actor].registre[125];
	env->hud.inventory[3] = env->action[type_actor].registre[126];
	env->hud.inventory[4] = env->action[type_actor].registre[127];
	env->hud.inventory[5] = env->action[type_actor].registre[128];
	env->hud.inventory[6] = env->action[type_actor].registre[129];
	env->hud.inventory[7] = env->action[type_actor].registre[130];
}

void		reg_to_global(t_env *env, int n, int type_actor)
{
	env->p.sector = env->action[type_actor].registre[119];
	env->p.pos.x = env->action[type_actor].registre[120];
	env->p.pos.y = env->action[type_actor].registre[121];
	env->p.pos.z = (float)env->action[type_actor].registre[122];
	recover_precision(env, n, type_actor);
	env->current_sentence = abs(env->action[type_actor].registre[131]);
	if (env->current_sentence >= NB_SENTENCES)
		env->current_sentence = 0;
	env->p.new_level = abs(env->action[type_actor].registre[118]);
	if (env->p.new_level >= NB_LEVELS)
		env->p.new_level = 0;
	update_hud(env, n, type_actor);
}
