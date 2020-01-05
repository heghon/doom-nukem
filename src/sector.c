/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 15:05:05 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/07 03:17:38 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	ft_mod(t_env *env, int i)
{
	if ((i - env->sector[env->wall[i - 1].sector].num_walls)
			== env->sector[env->wall[i - 1].sector].start_wall)
		return (env->sector[env->wall[i - 1].sector].start_wall);
	return (i);
}

int			inter_sector(t_env *env, t_sector *s, t_sector *z)
{
	int		i;
	int		j;

	i = s->start_wall - 1;
	while (++i < s->start_wall + s->num_walls)
	{
		j = z->start_wall - 1;
		while (++j < z->start_wall + z->num_walls)
		{
			if (segment_inter(env->wall[i].pos,
								env->wall[ft_mod(env, i + 1)].pos,
								env->wall[j].pos,
								env->wall[ft_mod(env, j + 1)].pos) == TRUE)
				return (TRUE);
		}
	}
	return (FALSE);
}

static void	adjust_sector(t_sector *s, int new_floor)
{
	if (s->floor < new_floor)
		s->floor = new_floor;
}

int			sector_correction(t_env *env, int sector)
{
	int		i;
	int		inter;

	i = -1;
	inter = FALSE;
	while (++i < env->card[e_sector])
	{
		if (i == sector)
			continue ;
		if (inter_sector(env, &env->sector[sector], &env->sector[i]) == TRUE)
		{
			adjust_sector(&env->sector[sector], env->sector[i].ceiling);
			inter = TRUE;
		}
	}
	return (inter);
}

void		re_update_walls(t_env *e, int s)
{
	int		i;
	int		start_wall;
	int		end_wall;

	start_wall = e->sector[s].start_wall;
	end_wall = e->sector[s].start_wall + e->sector[s].num_walls;
	i = start_wall - 1;
	while (++i < end_wall)
	{
		e->wall[i].floor = e->sector[s].floor;
		e->wall[i].ceiling = e->sector[s].ceiling;
	}
}
