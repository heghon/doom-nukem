/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 22:45:53 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:35:59 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				extract_font(t_env *env)
{
	int			i;
	int			j;
	int			k;
	int			offset;

	i = -1;
	while (ft_getchar(&(env->stream)) && ++i < NB_LETTERS)
	{
		j = -1;
		while (++j < HEIGHT_FONT)
		{
			k = -1;
			while (++k < WIDTH_FONT)
			{
				offset = (WIDTH_FONT * j + k) + i * HEIGHT_FONT * WIDTH_FONT;
				if (ft_strchr(".*", ft_getchar(&(env->stream))) == FALSE)
					return (header);
				env->letter[offset] = ft_getc(&(env->stream)) == '*' ? ON : OFF;
			}
			skip_space(&(env->stream));
		}
		skip_space(&(env->stream));
	}
	return (header);
}

static void		display_point(t_env *env, t_point *p)
{
	int			i;
	int			j;

	i = p->x;
	while (i < p->x + env->s_font)
	{
		j = p->y;
		while (j < p->y + env->s_font)
		{
			plot(&env->view, i, j);
			j++;
		}
		i++;
	}
}

void			display_letter(t_env *env, int i, t_point point)
{
	int			j;
	int			k;
	int			offset;
	int			start_x;

	j = -1;
	start_x = point.x;
	while (++j < HEIGHT_FONT)
	{
		k = -1;
		point.x = start_x;
		while (++k < WIDTH_FONT)
		{
			offset = (WIDTH_FONT * j + k) + i * HEIGHT_FONT * WIDTH_FONT;
			if (env->letter[offset] == ON)
				display_point(env, &point);
			point.x += env->s_font;
		}
		point.y += env->s_font;
	}
}

void			display_text(t_env *env, t_point point, char *text)
{
	int			start_x;

	brush_color(env, env->editor.color_text);
	start_x = point.x;
	while (*text)
	{
		if (*text == ';')
		{
			point.x = start_x;
			point.y += HEIGHT_FONT * env->s_font + MARGIN;
			text++;
			continue ;
		}
		if (*text >= 'a' && *text <= 'z')
			display_letter(env, *text - 'a', point);
		else if (*text >= 'A' && *text <= 'Z')
			display_letter(env, *text - 'A', point);
		else if (*text >= '0' && *text <= '9')
			display_number(env, *text - '0', point);
		else if (*text == '-')
			display_number(env, 10, point);
		point.x += WIDTH_FONT * env->s_font;
		text++;
	}
}

void			save_font(t_env *env)
{
	int			i;

	i = 0;
	ft_putstr(&env->stream_out, "[--[ FONT ]--]\n");
	ft_putc(&env->stream_out, '\n');
	while (i < NB_LETTERS * WIDTH_FONT * HEIGHT_FONT)
	{
		if (env->letter[i] == ON)
			ft_putc(&env->stream_out, '*');
		else
			ft_putc(&env->stream_out, '.');
		i++;
	}
	ft_putc(&env->stream_out, '\n');
	ft_putstr(&env->stream_out, "[--[ NUMBER ]--]\n");
	ft_putc(&env->stream_out, '\n');
	i = 0;
	while (i < NB_NUMBERS * WIDTH_NUM * HEIGHT_NUM)
	{
		if (env->number[i] == ON)
			ft_putc(&env->stream_out, '*');
		else
			ft_putc(&env->stream_out, '.');
		i++;
	}
}
