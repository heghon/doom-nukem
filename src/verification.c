/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseneca <sseneca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:36:05 by sseneca           #+#    #+#             */
/*   Updated: 2019/11/17 03:00:43 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_texture(t_env *env, int t)
{
	int	s;
	int	i;

	i = -1;
	s = 6;
	env->texture[t].w = s;
	env->texture[t].h = s;
	while (++i < s * s)
	{
		env->texture[t].picture[i * 4 + 1] = 0;
		env->texture[t].picture[i * 4 + 2] = 0;
		if (i % 2 == i / s % 2)
		{
			env->texture[t].picture[i * 4] = 200;
			env->texture[t].picture[i * 4 + 2] = 200;
		}
		else
			env->texture[t].picture[i * 4] = 1;
	}
	env->texture[t].size = 20;
}

static void	verif_object(t_env *env, int t)
{
	int	i;
	int	j;

	i = -1;
	while (++i < env->card[e_object])
	{
		if (env->object[i].a.texture < 0 || env->object[i].a.texture > t)
			env->object[i].a.texture = t;
		if (env->object[i].b.texture < 0 || env->object[i].b.texture > t)
			env->object[i].b.texture = t;
	}
	i = -1;
	while (++i < env->card[e_character])
	{
		j = -1;
		while (++j < 4)
			if (env->character[i].texture[j] < 0
				|| env->character[i].texture[j] > t)
				env->character[i].texture[j] = t;
	}
}

static void	verif_texture(t_env *env, int t)
{
	int	i;

	i = -1;
	while (++i < env->card[e_wall])
		if (env->wall[i].texture < 0 || env->wall[i].texture > t)
			env->wall[i].texture = t;
	i = -1;
	while (++i < env->card[e_sector])
	{
		if (env->sector[i].tex_f < 0 || env->sector[i].tex_f > t)
			env->sector[i].tex_f = t;
		if (env->sector[i].tex_c < 0 || env->sector[i].tex_c > t)
			env->sector[i].tex_c = t;
	}
	verif_object(env, t);
}

void		verification(t_env *env)
{
	init_texture(env, env->current_texture);
	verif_texture(env, env->current_texture);
}
