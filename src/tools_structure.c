/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_structure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 23:56:07 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/10 00:10:02 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	clockwise(t_env *env, int start, int end)
{
	float	edge;
	int		i;
	int		j;
	float	tmp;

	edge = 0;
	i = start;
	while (i <= end)
	{
		j = (i == end) ? start : i + 1;
		tmp = (env->wall[j].pos.x - env->wall[i].pos.x)
			* (env->wall[j].pos.y + env->wall[i].pos.y);
		edge += tmp;
		i++;
	}
	return (edge > 0);
}

static void	change_portail(t_env *env, int start, int end)
{
	int	i;
	int	j;
	int tmp;
	int	tex;

	i = start;
	tmp = env->wall[i].next_sector;
	tex = env->wall[i].texture;
	while (i <= end)
	{
		if (i == end)
		{
			env->wall[i].next_sector = tmp;
			env->wall[i].texture = tex;
		}
		else
		{
			j = i + 1;
			env->wall[i].next_sector = env->wall[j].next_sector;
			env->wall[i].texture = env->wall[j].texture;
		}
		i++;
	}
}

static void	sort_struct(t_env *env, int start, int end)
{
	t_wall	tmp;
	int		i;

	i = start;
	while ((float)i <= start + ((float)(end - start) / 2))
	{
		tmp = env->wall[i];
		env->wall[i] = env->wall[end - i + start];
		env->wall[end - i + start] = tmp;
		i++;
	}
	change_portail(env, start, end);
}

void		struct_direction(t_env *env)
{
	int	i;
	int	end;

	i = 0;
	while (i < env->card[e_sector])
	{
		end = (env->card[e_sector] == i + 1) ? env->card[e_wall] - 1
			: env->sector[i + 1].start_wall - 1;
		if (!clockwise(env, env->sector[i].start_wall, end))
			sort_struct(env, env->sector[i].start_wall, end);
		i++;
	}
}

int			same_wall(t_env *env, int sector, t_point j)
{
	int i;

	if (sector != -1)
	{
		i = env->sector[sector].start_wall;
		while (i < env->sector[sector].start_wall
				+ env->sector[sector].num_walls)
		{
			if (equal(j, env->wall[i].pos))
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}
