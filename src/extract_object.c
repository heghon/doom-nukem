/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:09:06 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:35:10 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		extract_word(t_stream *s)
{
	char		buff[42];

	stream_to_buff(s, buff);
	if (ft_strequ(buff, "object") == TRUE)
		return (e_object);
	else if (ft_strequ(buff, "character") == TRUE)
		return (e_character);
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

static int		extract_element(t_env *env)
{
	t_stream	*s;
	int			nb;

	s = &(env->stream);
	nb = ft_get_nb(s);
	while (nb-- && available_memory(env, e_object))
		fill_object(env);
	env->current_object = env->card[e_object];
	return (SUCCESS);
}

static int		extract_character(t_env *env)
{
	t_stream	*s;
	int			nb;

	s = &(env->stream);
	nb = ft_get_nb(s);
	while (nb-- && available_memory(env, e_character))
		fill_character(env);
	env->current_character = env->card[e_character];
	return (SUCCESS);
}

int				extract_object(t_env *env)
{
	int			type_bloc;
	t_stream	*s;

	s = &(env->stream);
	type_bloc = parse_sub_head(s);
	if (type_bloc == ERROR)
		return (data);
	if (type_bloc == e_object)
		extract_element(env);
	else if (type_bloc == e_character)
		extract_character(env);
	return (header);
}
