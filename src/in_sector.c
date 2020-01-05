/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_sector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:10:24 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/10 00:10:16 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	is_in_sector(t_env *env, int sector)
{
	int		i;
	int		j;
	int		c;
	int		end;
	t_float point;

	point = env->p.pos;
	end = (sector == env->card[e_sector] - 1) ? env->card[e_wall] - 1
		: env->sector[sector + 1].start_wall - 1;
	i = end;
	c = 0;
	while (sector != -1 && i >= env->sector[sector].start_wall)
	{
		j = (i == env->sector[sector].start_wall) ? end : i - 1;
		if ((((env->wall[i].pos.y <= point.y) && (point.y < env->wall[j].pos.y))
			|| ((env->wall[j].pos.y <= point.y)
			&& (point.y < env->wall[i].pos.y)))
			&& (point.x < (env->wall[j].pos.x - env->wall[i].pos.x)
			* (point.y - env->wall[i].pos.y)
			/ (env->wall[j].pos.y - env->wall[i].pos.y) + env->wall[i].pos.x))
			c = !c;
		i--;
	}
	return (c);
}

int	point_in_sector(t_env *env, int sector, t_point point)
{
	int i;
	int j;
	int c;
	int end;

	end = (sector == env->card[e_sector] - 1) ? env->card[e_wall] - 1
		: env->sector[sector + 1].start_wall - 1;
	i = end;
	c = 0;
	while (sector != -1 && i >= env->sector[sector].start_wall)
	{
		j = (i == env->sector[sector].start_wall) ? end : i - 1;
		if ((((env->wall[i].pos.y <= point.y) && (point.y < env->wall[j].pos.y))
			|| ((env->wall[j].pos.y <= point.y)
			&& (point.y < env->wall[i].pos.y)))
			&& (point.x < (env->wall[j].pos.x - env->wall[i].pos.x)
			* (point.y - env->wall[i].pos.y)
			/ (env->wall[j].pos.y - env->wall[i].pos.y) + env->wall[i].pos.x))
			c = !c;
		i--;
	}
	return (c);
}

int	in_which_sector(t_env *env)
{
	int	i;
	int	sector;

	i = 0;
	sector = -1;
	while (i < env->card[e_sector])
	{
		if (is_in_sector(env, i) && env->sector[i].ceiling > env->p.pos.z * 20
			&& env->sector[i].floor < env->p.pos.z * 20)
		{
			if (sector == -1)
				sector = i;
			else
			{
				if (point_in_sector(env, sector,
									env->wall[env->sector[i].start_wall].pos))
					sector = i;
			}
		}
		i++;
	}
	return (sector);
}

int	wall_in_sector(t_env *env, int k)
{
	int i;
	int j;
	int end;

	if (point_in_sector(env, env->rend.sector, env->wall[k].pos)
		|| point_in_sector(env, env->rend.sector, env->wall[k + 1].pos))
		return (env->rend.sector);
	end = (env->rend.sector == env->card[e_sector] - 1) ? env->card[e_wall] - 1
		: env->sector[env->rend.sector + 1].start_wall - 1;
	i = end;
	while (env->rend.sector != -1
				&& i >= env->sector[env->rend.sector].start_wall)
	{
		j = (i == env->sector[env->rend.sector].start_wall) ? end : i - 1;
		if (onsegment(env->wall[i].pos, env->wall[k].pos, env->wall[j].pos)
			|| onsegment(env->wall[i].pos,
									env->wall[k + 1].pos, env->wall[j].pos))
			return (env->rend.sector);
		i--;
	}
	return (env->wall[k].sector);
}

int	which_sector(t_env *env, int i)
{
	int	j;

	if (env->wall[i].sector == env->rend.sector)
		return (env->wall[i].sector);
	j = env->sector[env->wall[i].sector].start_wall;
	if (env->sector[env->wall[i].sector].num_walls == 2)
		return (wall_in_sector(env, j));
	while (j < env->sector[env->wall[i].sector].start_wall
			+ env->sector[env->wall[i].sector].num_walls)
	{
		if (!same_wall(env, env->rend.sector, env->wall[j].pos))
		{
			if (point_in_sector(env, env->rend.sector, env->wall[j].pos))
				return (env->rend.sector);
			else
				return (env->wall[i].sector);
		}
		j++;
	}
	return (env->wall[i].sector);
}
