/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_header.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:13:47 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 22:59:47 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		extract_word(t_stream *s)
{
	char		buff[42];

	stream_to_buff(s, buff);
	if (ft_strequ(buff, "MAP") == TRUE)
		return (map);
	else if (ft_strequ(buff, "TEXTURE") == TRUE)
		return (picture);
	else if (ft_strequ(buff, "OBJECT") == TRUE)
		return (element);
	else if (ft_strequ(buff, "ANIMATION") == TRUE)
		return (instruction);
	else if (ft_strequ(buff, "AUDIO") == TRUE)
		return (sound);
	else if (ft_strequ(buff, "FONT") == TRUE)
		return (font);
	else if (ft_strequ(buff, "NUMBER") == TRUE)
		return (number);
	else if (ft_strequ(buff, "PLAYER") == TRUE)
		return (level);
	else if (ft_strequ(buff, "TEXT") == TRUE)
		return (text);
	return (ERROR);
}

static int		parse_head(t_stream *s)
{
	int			type_bloc;

	skip_space(s);
	if (fts_equal(s, "[--[") == FALSE)
		return (ERROR);
	skip_space(s);
	type_bloc = extract_word(s);
	skip_space(s);
	if (fts_equal(s, "]--]") == FALSE)
		return (ERROR);
	skip_space(s);
	return (type_bloc);
}

int				extract_header(t_env *env)
{
	int			type_bloc;
	t_stream	*s;

	s = &(env->stream);
	type_bloc = parse_head(s);
	if (type_bloc == ERROR)
		return (data);
	return (type_bloc);
}
