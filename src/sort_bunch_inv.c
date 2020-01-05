/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bunch_inv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:30:23 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/10 00:07:23 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	inv_to_vis(t_env *env, int i, int j, int previous[3])
{
	if (env->rend.wall[0][env->rend.bunch[0][i].start_wall].w.sector
		== env->rend.wall[1][env->rend.bunch[1][j].start_wall].w.sector
		&& previous[1] == 0
		&& env->rend.bunch[0][i].inv == -1)
	{
		previous[1] = 1;
		env->rend.bunch[0][i].inv = j;
		if (env->rend.first_bunch[1] == j)
			env->rend.first_bunch[1] = env->rend.bunch[1][j].next;
		else
			env->rend.bunch[1][previous[0]].next = env->rend.bunch[1][j].next;
	}
	return (previous[1]);
}

static int	inv1_to_vis(t_env *env, int i, int j, int previous[3])
{
	if (i != -1 && j != -1 && is_in_sector(env, env->rend.wall[1]
		[env->rend.bunch[1][j].start_wall].w.sector)
		&& test_height_sector(env, j, i, 1) != 0
		&& previous[2] == 0)
	{
		previous[2] = 1;
		env->rend.bunch[0][i].inv1 = j;
		if (env->rend.first_bunch[1] == j)
			env->rend.first_bunch[1] = env->rend.bunch[1][j].next;
		else
			env->rend.bunch[1][previous[0]].next = env->rend.bunch[1][j].next;
	}
	return (previous[2]);
}

void		sort_bunch_inv(t_env *env)
{
	int i[2];
	int previous[4];

	i[0] = env->rend.first_bunch[0];
	previous[2] = 0;
	while (i[0] != -1 && i[0] != env->rend.all)
	{
		i[1] = env->rend.first_bunch[1];
		env->rend.bunch[0][i[0]].inv = -1;
		env->rend.bunch[0][i[0]].inv1 = -1;
		previous[0] = -1;
		previous[1] = 0;
		while (i[1] != -1 && i[1] != env->rend.all)
		{
			previous[3] = previous[2];
			previous[2] = inv1_to_vis(env, i[0], i[1], previous);
			if (previous[3] == previous[2])
			{
				previous[1] = inv_to_vis(env, i[0], i[1], previous);
				previous[0] = i[1];
			}
			i[1] = env->rend.bunch[1][i[1]].next;
		}
		i[0] = env->rend.bunch[0][i[0]].next;
	}
}
