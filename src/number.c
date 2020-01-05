/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:49:23 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/07 03:14:08 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				extract_number(t_env *env)
{
	int			i;
	int			j;
	int			k;
	int			offset;

	i = -1;
	while (ft_getchar(&(env->stream)) && ++i < NB_LETTERS)
	{
		j = -1;
		while (++j < HEIGHT_NUM)
		{
			k = -1;
			while (++k < WIDTH_NUM)
			{
				offset = (WIDTH_NUM * j + k) + i * HEIGHT_NUM * WIDTH_NUM;
				if (ft_strchr(".*", ft_getchar(&(env->stream))) == FALSE)
					return (header);
				env->number[offset] = ft_getc(&(env->stream)) == '*' ? ON : OFF;
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

void			display_number(t_env *env, int i, t_point point)
{
	int			j;
	int			k;
	int			offset;
	int			start_x;

	j = -1;
	start_x = point.x;
	while (++j < HEIGHT_NUM)
	{
		k = -1;
		point.x = start_x;
		while (++k < WIDTH_NUM)
		{
			offset = (WIDTH_NUM * j + k) + i * HEIGHT_NUM * WIDTH_NUM;
			if (env->number[offset] == ON)
				display_point(env, &point);
			point.x += env->s_font;
		}
		point.y += env->s_font;
	}
}

void			display_value(t_env *env, t_point point, int value)
{
	int			chiffre;
	int			is_neg;

	is_neg = FALSE;
	brush_color(env, env->editor.color_text);
	if (value < 0)
	{
		is_neg = TRUE;
		value = value * (-1);
	}
	while (value >= 10)
	{
		chiffre = value % 10;
		display_number(env, chiffre, point);
		point.x -= WIDTH_NUM * env->s_font;
		value /= 10;
	}
	chiffre = value % 10;
	display_number(env, chiffre, point);
	point.x -= WIDTH_NUM * env->s_font;
	if (is_neg == TRUE)
		display_number(env, 10, point);
}
