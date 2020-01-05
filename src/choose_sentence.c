/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_sentence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseneca <sseneca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 15:32:09 by sseneca           #+#    #+#             */
/*   Updated: 2019/12/10 00:02:16 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	reset_obj(t_env *env)
{
	int i;
	int j;

	i = -1;
	while (++i < env->card[e_object])
	{
		j = -1;
		while (j++ < env->nb_sentence)
		{
			if (env->sentence[j].obj == i && env->object[i].pickable > 0
			&& env->object[i].pickable == 2 && j != env->current_sentence
			&& env->object[i].prio == 0)
				env->object[i].pickable = 1;
		}
	}
}

void		choose_sentence(t_env *env)
{
	int i;

	i = -1;
	env->view.main_layer = render_layer;
	env->view.color = adapt_luminosity(0xEEEEEE,
	env->sector[env->p.sector].luminosity);
	while (++i < env->nb_sentence)
	{
		if (env->sentence[i].obj > -1
		&& env->sentence[i].obj < env->card[e_object])
		{
			if (env->object[env->sentence[i].obj].pickable == 2)
			{
				env->current_sentence = i;
				reset_obj(env);
			}
		}
	}
	i = -1;
	while (++i < env->card[e_object])
		env->object[i].prio = 0;
}

void		save_sentences(t_env *env)
{
	int		i;

	i = 0;
	ft_putstr(&env->stream_out, "[--[ TEXT ]--]\n");
	ft_putstr(&env->stream_out, "== sentences == ");
	write_value(env->nb_sentence, &env->stream_out);
	ft_putc(&env->stream_out, '\n');
	while (i < env->nb_sentence)
	{
		write_value(env->sentence[i].p.x, &env->stream_out);
		write_value(env->sentence[i].p.y, &env->stream_out);
		write_value(env->sentence[i].color, &env->stream_out);
		write_value(env->sentence[i].obj, &env->stream_out);
		ft_putc(&env->stream_out, '\"');
		ft_putstr(&env->stream_out, env->sentence[i].str);
		ft_putc(&env->stream_out, '\"');
		ft_putc(&env->stream_out, '\n');
		i++;
	}
	ft_putc(&env->stream_out, '\n');
}
