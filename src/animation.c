/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:03:03 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/10 00:39:11 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			animate_actor(t_env *env, int type_actor, int i)
{
	type_actor = load_attribute(env, type_actor, i);
	read_instruction(env, type_actor);
	save_attribute(env, type_actor, i);
}

static int		animate_content(t_env *env, int type_actor)
{
	int			i;

	i = -1;
	while (++i < env->card[type_actor])
		animate_actor(env, type_actor, i);
	return (SUCCESS);
}

int				animate_game(t_env *env)
{
	static int	level = 0;

	animate_content(env, e_sector);
	animate_content(env, e_object);
	if (env->p.new_level != level)
	{
		level = env->p.new_level;
		get_position(env, &env->p);
	}
	return (SUCCESS);
}
