/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseneca <sseneca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 16:55:57 by sseneca           #+#    #+#             */
/*   Updated: 2019/12/09 23:50:36 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	distance_object(t_env *env, t_object *o, int max)
{
	float distance;
	float fx;
	float fy;

	fx = (float)o->pos.x;
	fy = (float)o->pos.y;
	distance = pythagore4(env->p.pos.x, fx, env->p.pos.y, fy);
	if (o->a.floor > env->p.pos.z * 20 + 10
			|| o->b.floor > env->p.pos.z * 20 + 10
			|| o->a.ceiling + 10 < env->p.pos.z * 20
			|| o->b.ceiling + 10 < env->p.pos.z * 20)
		return (0);
	else if (distance < max)
		return (1);
	else
		return (0);
}

static void	clean_inventory(t_hud *hud)
{
	int i;
	int j;

	i = -1;
	while (++i < 8)
	{
		if (hud->inventory[i] == -1)
		{
			j = i;
			while (++j < 8)
			{
				if (hud->inventory[j] != -1)
				{
					hud->inventory[i] = hud->inventory[j];
					hud->inventory[j] = -1;
					i = j;
				}
			}
		}
	}
}

static void	update_inventory(t_env *env, t_hud *hud)
{
	int i[2];

	i[0] = -1;
	while (++i[0] < env->card[e_object])
		if (env->object[i[0]].pickable == 2 && hud->nb_inventory < 8)
		{
			i[1] = -1;
			while (++i[1] < 8)
				if (hud->inventory[i[1]] == i[0])
					i[1] = 9;
			if (i[1] == 8)
				hud->inventory[hud->nb_inventory++] = i[0];
		}
	i[0] = -1;
	while (++i[0] < (int)hud->nb_inventory)
		if (hud->inventory[i[0]] != -1
			&& env->object[hud->inventory[i[0]]].pickable != 2)
		{
			i[1] = i[0] - 1;
			while (++i[1] < 7)
				hud->inventory[i[1]] = hud->inventory[i[1] + 1];
			hud->inventory[7] = -1;
			hud->nb_inventory--;
		}
	clean_inventory(hud);
}

static void	check_effect(t_env *env, int e)
{
	if (e < 0 && env->p.timer == env->p.total_time)
	{
		env->p.timer += abs(e);
		return ;
	}
	env->hud.timer = OFF;
	env->hud.compass = OFF;
	if (e >= 16)
		env->hud.timer = ON;
	if (e >= 16)
		e -= 16;
	if (e >= 8)
		env->hud.compass = ON;
	if (e >= 8)
		e -= 8;
	if (e >= 4)
		env->p.gun = ON;
	if (e >= 4)
		e -= 4;
	if (e >= 2)
		env->p.wings = ON;
	if (e >= 2)
		e -= 2;
	if (e >= 1)
		env->p.sprint = ON;
}

void		check_object(t_env *env, t_hud *hud)
{
	int i;

	i = -1;
	while (++i < env->card[e_object])
		if (env->object[i].pickable % 2 == 1
			&& distance_object(env, &env->object[i], 21))
		{
			check_effect(env, env->object[i].effect);
			if (env->object[i].nl == 1)
			{
				env->p.new_level += env->nb_level
				== env->p.new_level ? -env->nb_level : env->object[i].nl;
				env->object[i].nl = 0;
			}
			else
				env->object[i].pickable += ++env->object[i].prio;
		}
	i = -1;
	while (++i < 8)
		if (hud->bu[i] != hud->inventory[i] && hud->inventory[i] == -1)
			env->object[hud->bu[i]].pickable = 1;
	update_inventory(env, hud);
	i = -1;
	while (++i < 8)
		hud->bu[i] = hud->inventory[i];
}
