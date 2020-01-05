/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 07:07:14 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 20:23:53 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			save_character(t_env *env)
{
	int			i;

	i = 0;
	ft_putstr(&env->stream_out, "[--[ OBJECT ]--]\n");
	ft_putstr(&env->stream_out, "== character == ");
	write_value(env->card[e_character], &env->stream_out);
	ft_putc(&env->stream_out, '\n');
	while (i < env->card[e_character])
	{
		write_value(env->character[i].o.pos.x, &env->stream_out);
		write_value(env->character[i].o.pos.y, &env->stream_out);
		write_value(env->character[i].o.a.floor, &env->stream_out);
		write_value(env->character[i].o.a.ceiling, &env->stream_out);
		write_value(env->character[i].texture[0], &env->stream_out);
		write_value(env->character[i].texture[1], &env->stream_out);
		write_value(env->character[i].texture[2], &env->stream_out);
		write_value(env->character[i].texture[3], &env->stream_out);
		write_value(env->character[i].animated, &env->stream_out);
		write_value(env->character[i].reaction, &env->stream_out);
		ft_putc(&env->stream_out, '\n');
		i++;
	}
}

void			fill_character(t_env *env)
{
	t_stream	*s;
	int			card;

	s = &(env->stream);
	card = env->card[e_character];
	env->character[card].o.pos.x = ft_get_nb(s);
	env->character[card].o.pos.y = ft_get_nb(s);
	env->character[card].o.a.floor = ft_get_nb(s);
	env->character[card].o.a.ceiling = ft_get_nb(s);
	env->character[card].o.b.floor = env->character[card].o.a.floor;
	env->character[card].o.b.ceiling = env->character[card].o.a.ceiling;
	env->character[card].texture[0] = get_val(s, 0, NB_TEXTURES);
	env->character[card].texture[1] = get_val(s, 0, NB_TEXTURES);
	env->character[card].texture[2] = get_val(s, 0, NB_TEXTURES);
	env->character[card].texture[3] = get_val(s, 0, NB_TEXTURES);
	env->character[card].color = 0xFFFFFF;
	env->character[card].animated = get_val(s, 0, 1);
	env->character[card].reaction = get_val(s, 0, NB_REACTIONS);
	env->character[card].dead = 0;
	env->card[e_character]++;
}

void			update_character_extra(t_env *env, int sign)
{
	int			value;
	int			*p_val;
	int			*p_val2;

	if (env->editor.attribut[e_character][5] == ON)
	{
		p_val = &env->character[env->editor.select[e_character]].o.a.floor;
		p_val2 = &env->character[env->editor.select[e_character]].o.b.floor;
		value = update_value(p_val, sign, MIN_ALTITUDE, MAX_ALTITUDE);
		*p_val2 = value;
		env->editor.attribut_value = value;
	}
	else if (env->editor.attribut[e_character][6] == ON)
	{
		p_val = &env->character[env->editor.select[e_character]].o.a.ceiling;
		p_val2 = &env->character[env->editor.select[e_character]].o.b.ceiling;
		value = update_value(p_val, sign, MIN_ALTITUDE, MAX_ALTITUDE);
		*p_val2 = value;
		env->editor.attribut_value = value;
	}
}
