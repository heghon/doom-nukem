/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:06:28 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/09 20:42:19 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	display_bunch(t_env *env, int i)
{
	int j;
	int	k;

	j = env->rend.bunch[env->rend.see][i].start_wall;
	if (j != -1)
	{
		env->rend.wall[env->rend.see][j].w.dist = dist_wall(env,
			env->rend.wall[env->rend.see][j].w.p);
		while (env->rend.wall[env->rend.see][j].next != env->rend.all
			&& env->rend.wall[env->rend.see][j].next != -1)
		{
			k = env->rend.wall[env->rend.see][j].next;
			env->rend.wall[env->rend.see][k].w.dist = dist_wall(env,
				env->rend.wall[env->rend.see][k].w.p);
			if (env->rend.wall[env->rend.see][k].w.next_sector != -1
				&& env->rend.see == visible)
				add_portal(env, j, k);
			display_wall(env, &env->rend.wall[env->rend.see][j].w,
				&env->rend.wall[env->rend.see][k].w);
			j = k;
		}
	}
	i = env->rend.bunch[env->rend.see][i].next;
	return (i);
}

static void	display_inv_bunch(t_env *env, int v)
{
	env->rend.see = invisible;
	if (v != env->rend.all && v != -1)
		display_bunch(env, v);
	env->rend.see = visible;
}

void		display_sector(t_env *env)
{
	int	i;

	i = env->rend.first_bunch[0];
	while (i != -1 && i != env->rend.all)
	{
		display_inv_bunch(env, env->rend.bunch[0][i].inv1);
		display_bunch(env, i);
		display_inv_bunch(env, env->rend.bunch[0][i].inv);
		i = env->rend.bunch[0][i].next;
	}
	if (env->rend.first_portal != -1
			&& env->rend.first_portal != env->rend.all && env->rend.port == 1)
		env->rend.first_portal = env->rend.portal[env->rend.first_portal].next;
	if (env->rend.first_portal != env->rend.all)
		render(env);
	env->p.pos = env->p.tmp_pos;
	env->p.dir = env->p.tmp_dir;
	init_fov(env);
	if (env->rend.sector != -1)
		display_hud(env, &env->hud);
	display_cross(env);
	env->rend.euc = OFF;
}
