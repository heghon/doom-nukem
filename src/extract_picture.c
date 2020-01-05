/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_picture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 19:13:28 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 07:42:57 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		extract_word(t_stream *s)
{
	char		buff[42];

	stream_to_buff(s, buff);
	if (ft_strequ(buff, "pictures") == TRUE)
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

static int		extract_one(t_env *env)
{
	t_stream	*s;
	int			dim;
	int			i;
	int			current_texture;

	i = 0;
	s = &(env->stream);
	current_texture = env->current_texture;
	env->texture[env->current_texture].w = get_val(s, 1, MAX_PIXEL + 1);
	env->texture[env->current_texture].h = get_val(s, 1, MAX_PIXEL + 1);
	env->texture[env->current_texture].size = get_val(s, 1, MAX_DIST);
	dim = env->texture[env->current_texture].w
		* env->texture[env->current_texture].h * 4;
	while (dim--)
		if (dim % 4 != 0)
			env->texture[current_texture].picture[i++] = get_val(s, 0, 255);
		else
			env->texture[current_texture].picture[i++] = 0;
	env->current_texture++;
	env->card[e_texture]++;
	return (SUCCESS);
}

int				extract_picture(t_env *env)
{
	int			nb;
	int			type_bloc;
	t_stream	*s;

	s = &(env->stream);
	type_bloc = parse_sub_head(s);
	if (type_bloc == ERROR)
		return (data);
	nb = get_val(s, 0, NB_TEXTURES);
	while (nb-- && available_memory(env, e_texture))
		extract_one(env);
	return (header);
}
