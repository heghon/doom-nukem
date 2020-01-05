/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 21:11:14 by sseneca           #+#    #+#             */
/*   Updated: 2019/12/09 21:30:25 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <math.h>

/*
**compare la direction du joueur et du monstre pour choisir le bon sprite
*/

int			compare_dir(t_float p, t_float m)
{
	float	atan[2];
	float	diff;

	atan[0] = atan2(p.x, p.y);
	atan[1] = atan2(m.x, m.y);
	if (atan[0] < 0)
		atan[0] = (M_PI * 2) + atan[0];
	if (atan[1] < 0)
		atan[1] = (M_PI * 2) + atan[1];
	atan[0] *= 57.2958;
	atan[1] *= 57.2958;
	diff = atan[0] - atan[1];
	if (diff > 225 || diff < 45)
		return (diff > 225 && diff < 315 ? 1 : 0);
	else
		return (diff < 135 ? 3 : 2);
}

/*
**Prends un object, et remplit avec les bonnes valeurs
*/

static void	setup_object(t_env *env, t_object *obj)
{
	float dist;

	env->p.perp.x = env->p.dir.y;
	env->p.perp.y = -env->p.dir.x;
	dist = env->texture[obj->a.texture].size / (float)2.0;
	obj->a.pos.x = obj->pos.x + (-env->p.perp.x * dist);
	obj->a.pos.y = obj->pos.y + (-env->p.perp.y * dist);
	obj->b.pos.x = obj->pos.x + (env->p.perp.x * dist);
	obj->b.pos.y = obj->pos.y + (env->p.perp.y * dist);
	obj->a.next_sector = -1;
	obj->b.next_sector = -1;
	obj->a.sector = -1;
	obj->b.sector = -1;
	screen_x(env, &obj->a);
	screen_x(env, &obj->b);
}

static void	add(t_env *env, t_wall a, t_wall b)
{
	if (!left_to_right(&env->p, a.pos, b.pos))
		add_to_bunch2(env, a, b, 1);
	else
		add_to_bunch1(env, a, b, 1);
}

void		add_sprite(t_env *env)
{
	int i;

	i = -1;
	env->rend.see = visible;
	while (++i < env->card[e_character])
	{
		if (is_in_range(env, env->character[i].o.a, env->character[i].o.b)
			&& point_in_sector(env, env->rend.sector,
											env->character[i].o.a.pos))
		{
			add(env, env->character[i].o.a, env->character[i].o.b);
		}
	}
	i = -1;
	while (++i < env->card[e_object])
	{
		if (is_in_range(env, env->object[i].a, env->object[i].b)
			&& point_in_sector(env, env->rend.sector, env->object[i].a.pos)
			&& env->object[i].pickable != 2)
			add(env, env->object[i].a, env->object[i].b);
	}
}

/*
**Appelle les bonnes fonctions pour tous les t_character et t_object
*/

void		setup_sprite(t_env *env)
{
	int		i;

	i = -1;
	while (++i < env->card[e_character])
	{
		env->character[i].o.a.texture = env->character[i].texture
			[compare_dir(env->p.dir, env->character[i].dir)];
		env->character[i].o.b.texture = env->character[i].texture
			[compare_dir(env->p.dir, env->character[i].dir)];
		setup_object(env, &env->character[i].o);
	}
	i = -1;
	while (++i < env->card[e_object])
		setup_object(env, &env->object[i]);
	add_sprite(env);
}
