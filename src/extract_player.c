/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:52:12 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:35:42 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		extract_word(t_stream *s)
{
	char		buff[42];

	stream_to_buff(s, buff);
	if (ft_strequ(buff, "level") == TRUE)
		return (e_player);
	return (ERROR);
}

static int		parse_sub_head(t_stream *s)
{
	int			type_bloc;

	skip_space(s);
	if (fts_equal(s, "==") == FALSE)
		return (ERROR);
	skip_space(s);
	type_bloc = extract_word(s);
	skip_space(s);
	if (fts_equal(s, "==") == FALSE)
		return (ERROR);
	skip_space(s);
	return (type_bloc);
}

static int		extract_level(t_env *env)
{
	t_stream	*s;
	int			nb;
	int			i;

	s = &(env->stream);
	nb = get_val(s, 1, NB_LEVELS + 1);
	env->p.nb_levels = nb;
	i = -1;
	while (++i < nb)
	{
		env->p.levels[i].x = get_val(s, MIN_ALTITUDE, MAX_ALTITUDE);
		env->p.levels[i].y = get_val(s, MIN_ALTITUDE, MAX_ALTITUDE);
		env->p.levels[i].z = get_val(s, MIN_ALTITUDE, MAX_ALTITUDE);
	}
	env->nb_level = nb;
	return (SUCCESS);
}

int				extract_player(t_env *env)
{
	int			type_bloc;
	t_stream	*s;

	s = &(env->stream);
	type_bloc = parse_sub_head(s);
	if (type_bloc == ERROR)
		return (data);
	if (type_bloc == e_player)
		extract_level(env);
	return (header);
}
