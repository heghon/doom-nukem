/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 06:25:56 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/14 07:19:55 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			save_player(t_env *env)
{
	int			i;

	i = 0;
	ft_putstr(&env->stream_out, "[--[ PLAYER ]--]\n");
	ft_putstr(&env->stream_out, "== level == ");
	write_value(env->p.nb_levels, &env->stream_out);
	ft_putc(&env->stream_out, '\n');
	while (i < env->p.nb_levels)
	{
		write_value(env->p.levels[i].x, &env->stream_out);
		write_value(env->p.levels[i].y, &env->stream_out);
		write_value(env->p.levels[i].z, &env->stream_out);
		ft_putc(&env->stream_out, '\n');
		i++;
	}
	ft_putc(&env->stream_out, '\n');
}
