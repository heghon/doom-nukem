/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 14:20:14 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:34:51 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		extract_word(t_stream *s)
{
	char		buff[42];

	stream_to_buff(s, buff);
	if (ft_strequ(buff, "sectors") == TRUE)
		return (SUCCESS);
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

static int		extract_wall(t_env *env)
{
	int			card;
	int			current_sector;
	int			relative_wall;

	card = env->card[e_wall];
	env->current_wall = 0;
	current_sector = 0;
	relative_wall = 0;
	while (card-- && available_memory(env, e_wall))
	{
		if (relative_wall == env->sector[current_sector].num_walls
			&& !(relative_wall = 0))
			current_sector++;
		fill_wall(env, current_sector);
		env->current_wall++;
		relative_wall++;
	}
	return (SUCCESS);
}

static int		extract_sector(t_env *env)
{
	t_stream	*s;
	int			nb;

	s = &(env->stream);
	nb = get_val(s, 0, NB_SECTORS);
	while (nb-- && available_memory(env, e_sector))
	{
		fill_sector(env, env->card[e_sector]);
		env->card[e_wall] += env->sector[env->card[e_sector]].num_walls;
		env->card[e_sector]++;
	}
	env->current_sector = env->card[e_sector];
	return (SUCCESS);
}

int				extract_map(t_env *env)
{
	int			type_bloc;
	t_stream	*s;

	s = &(env->stream);
	type_bloc = parse_sub_head(s);
	if (type_bloc == ERROR)
		return (data);
	extract_sector(env);
	extract_wall(env);
	return (header);
}
