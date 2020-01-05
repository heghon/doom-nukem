/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 21:24:09 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/07 03:05:08 by mbenjell         ###   ########.fr       */
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

int			correct_sector(t_env *env)
{
	int		current_wall;

	current_wall = env->current_wall;
	if (current_wall > 0
		&& equal_points(&env->editor.cursor, &env->wall[current_wall - 1].pos))
	{
		key_c(env);
		return (FALSE);
	}
	return (TRUE);
}

int			correct_polygon(t_env *env)
{
	if (env->sector[env->current_sector].num_walls < 3)
	{
		key_c(env);
		return (FALSE);
	}
	return (TRUE);
}

static int	correct_close(t_env *env)
{
	int		i;
	int		j;

	j = env->current_sector;
	i = env->sector[j].start_wall;
	while (++i < (env->card[e_wall] + env->sector[j].num_walls - 2))
	{
		if (segment_inter(env->editor.start_line, env->editor.cursor,
				env->wall[i].pos, env->wall[ft_mod(env, i + 1)].pos) == TRUE)
			return (FALSE);
	}
	return (TRUE);
}

int			correct_wall(t_env *env)
{
	int		i;
	int		j;

	j = env->current_sector;
	i = env->sector[j].start_wall - 1;
	if (env->sector[j].num_walls < 3)
		return (TRUE);
	while (++i < (env->card[e_wall] + env->sector[j].num_walls - 2))
	{
		if (segment_inter(env->editor.start_line, env->editor.cursor,
				env->wall[i].pos, env->wall[ft_mod(env, i + 1)].pos) == TRUE)
		{
			if (equal_points(&env->editor.cursor, &env->editor.start_polygon))
				return (correct_close(env));
			return (FALSE);
		}
	}
	return (TRUE);
}
