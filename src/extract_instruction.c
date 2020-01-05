/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 02:35:02 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:34:36 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		extract_word(t_stream *s)
{
	char		buff[42];

	stream_to_buff(s, buff);
	if (ft_strequ(buff, "player") == TRUE)
		return (e_player);
	else if (ft_strequ(buff, "character") == TRUE)
		return (e_character);
	else if (ft_strequ(buff, "object") == TRUE)
		return (e_object);
	else if (ft_strequ(buff, "sector") == TRUE)
		return (e_sector);
	else if (ft_strequ(buff, "wall") == TRUE)
		return (e_wall);
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

int				extract_param(t_stream *s)
{
	int			c;

	if (ft_getchar(s) == LABEL_REG)
	{
		ft_getc(s);
		c = ft_getchar(s);
		if (ft_strchr(SPACE, c))
			return (ERROR);
		return (get_val(s, 0, NB_REGISTERS));
	}
	return (ERROR);
}

int				extract_code(t_env *env)
{
	int			actor;
	t_stream	*s;
	int			i;

	s = &(env->stream);
	i = get_val(s, 0, NB_ACTORS * NB_REACTIONS);
	while (i--)
	{
		actor = parse_sub_head(s);
		if (actor == ERROR)
			return (data);
		if (available_action(env, actor) == FALSE)
			break ;
		actor = actor + NB_ACTORS * env->card_action[actor]++;
		extract_asm(env, actor);
	}
	return (header);
}
