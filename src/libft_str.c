/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:37:50 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/07 03:09:30 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

size_t		ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strchr(const char *s, int c)
{
	return (ft_memchr((const void*)s, c, ft_strlen(s) + 1));
}

int			ft_strequ(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (TRUE);
		s1++;
		s2++;
	}
	return (FALSE);
}

int			fts_equal(t_stream *stream, char *s)
{
	while (*s)
	{
		if (*s != ft_getchar(stream))
			return (FALSE);
		s++;
		ft_getc(stream);
	}
	return (TRUE);
}

int			stream_to_buff(t_stream *s, char *buff)
{
	int		k;

	k = 0;
	while ((ft_getchar(s)))
	{
		if (ft_strchr(SPACE, ft_getchar(s)))
			break ;
		buff[k++] = ft_getc(s);
		if (k == 12)
			return (ERROR);
	}
	buff[k] = '\0';
	return (SUCCESS);
}
