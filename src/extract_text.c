/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 03:07:32 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:35:53 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		extract_word(t_stream *s)
{
	char		buff[42];

	stream_to_buff(s, buff);
	if (ft_strequ(buff, "sentences") == TRUE)
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

static int		extract_sentences(t_env *env)
{
	t_stream	*s;
	int			i[2];
	int			nb;

	i[0] = -1;
	s = &(env->stream);
	nb = get_val(s, 0, NB_SENTENCES);
	env->nb_sentence = 0;
	while (++i[0] < nb && ++env->nb_sentence)
	{
		i[1] = -1;
		env->sentence[i[0]].p.x = get_val(s, 0, SIDE);
		env->sentence[i[0]].p.y = get_val(s, 0, SIDE);
		env->sentence[i[0]].color = get_val(s, 0, 16777216);
		env->sentence[i[0]].obj = get_val(s, -1, NB_OBJECTS);
		skip_space(s);
		if (ft_getc(s) != '\"')
			return (ERROR);
		while (++i[1] < NB_CHARS && ft_getchar(s) != '\"')
			env->sentence[i[0]].str[i[1]] = ft_getc(s);
		if (ft_getc(s) != '\"')
			return (ERROR);
		skip_space(s);
	}
	return (SUCCESS);
}

int				extract_text(t_env *env)
{
	int			type_bloc;
	t_stream	*s;

	s = &(env->stream);
	type_bloc = parse_sub_head(s);
	if (type_bloc == ERROR)
		return (data);
	extract_sentences(env);
	return (header);
}
