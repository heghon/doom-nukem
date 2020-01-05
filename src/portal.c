/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 00:35:09 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/07 03:14:53 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	same_line(t_point a, t_point b, t_point c, t_point d)
{
	if (equal(a, c) && equal(b, d))
		return (TRUE);
	if (equal(a, d) && equal(b, c))
		return (TRUE);
	return (FALSE);
}

static int	ft_mod(t_env *env, int i)
{
	if ((i - env->sector[env->wall[i - 1].sector].num_walls)
			== env->sector[env->wall[i - 1].sector].start_wall)
		return (env->sector[env->wall[i - 1].sector].start_wall);
	return (i);
}

static int	add_portal2(t_wall *w, t_wall *v)
{
	w->next_sector = v->sector;
	v->next_sector = w->sector;
	return (1);
}

static int	create_portal(t_env *env, t_sector *s, t_sector *z)
{
	int		i;
	int		j;
	int		ret;

	i = s->start_wall - 1;
	ret = 0;
	while (++i < s->start_wall + s->num_walls)
	{
		j = z->start_wall - 1;
		while (++j < z->start_wall + z->num_walls)
		{
			if (same_line(env->wall[i].pos, env->wall[ft_mod(env, i + 1)].pos,
				env->wall[j].pos, env->wall[ft_mod(env, j + 1)].pos) == TRUE)
				ret |= add_portal2(&env->wall[i], &env->wall[j]);
		}
	}
	return (ret);
}

int			connect_sector(t_env *env, int index_sector)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	while (++i < env->card[e_sector])
	{
		if (i == index_sector)
			continue ;
		ret |= create_portal(env, &env->sector[index_sector], &env->sector[i]);
	}
	return (ret);
}
