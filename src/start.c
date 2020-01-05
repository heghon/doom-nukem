/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseneca <sseneca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 17:10:05 by sseneca           #+#    #+#             */
/*   Updated: 2019/12/06 22:51:35 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	check_key_start(t_env *env, int *pos, int min, int max)
{
	static int	up;
	static int	down;

	if (env->keys[SDLK_UP % 42] == ON && up == 0)
	{
		*pos = *pos == min ? min : *pos - 1;
		up = 1;
	}
	else if (env->keys[SDLK_UP % 42] == OFF)
		up = 0;
	if (env->keys[SDLK_DOWN % 42] == ON && down == 0)
	{
		down = 1;
		*pos = *pos == max ? max : *pos + 1;
	}
	else if (env->keys[SDLK_DOWN % 42] == OFF)
		down = 0;
}

static void	display_start(t_env *env, int pos, int c)
{
	t_point		pi;
	char		*str;
	t_point		p[4];

	p[0].x = SIDE / 2 - SIDE / 7 / 2;
	p[0].y = SIDE / 6 * (c + 2) - (HEIGHT_FONT * env->s_font);
	p[1].x = SIDE / 2 + SIDE / 7 / 2;
	p[1].y = SIDE / 6 * (c + 2) - (HEIGHT_FONT * env->s_font);
	display_box(env, p, SIDE / 6 * (c + 2), pos == c ? 1 : 0);
	env->editor.color_text = pos == c ? 0xAA0000 : 0;
	str = c == 0 ? "play" : "editor";
	str = c == 2 ? "options" : str;
	pi.x = SIDE / 2 - (ft_strlen(str) * (WIDTH_FONT * env->s_font) / 2);
	pi.y = SIDE / 6 * (c + 2);
	display_text(env, pi, str);
}

void		random_handler_start(int *px, int *py, char **s, int ran[3])
{
	static int	u[6];

	if (ran[0] % 300 == 0 && u[1] == 0)
	{
		u[1] = 20;
		u[2] = ran[1] % (ft_strlen(s[0]) == 0 ? 1 : ft_strlen(s[0]));
		u[3] = ran[0] % abs(s[0][u[2]] - 122 == 0 ? 1 : s[0][u[2]] - 122);
		s[0][u[2]] += u[3];
	}
	if (ran[0] % 600 == 0 && u[0] == 0)
	{
		u[0] = 15;
		u[4] = ran[1] % 2 == 0 ? ran[1] % (SIDE / 40) : -ran[1] % (SIDE / 40);
		u[5] = ran[1] % 4 >= 2 ? ran[2] % (SIDE / 40) : -ran[2] % (SIDE / 40);
	}
	if (u[1] >= 1)
		u[1]--;
	if (u[1] == 1)
		s[0][u[2]] -= u[3];
	if (u[0] > 0)
	{
		*px += u[4];
		*py += u[5];
		u[0]--;
	}
}

void		display_title(t_env *env)
{
	char		*s;
	t_point		p;
	static int	color = 0xFF0000;
	static int	u[2];
	int			random[4];

	random[0] = rand();
	random[1] = rand();
	random[2] = rand();
	random[3] = env->s_font;
	u[0]++;
	s = env->file_name;
	env->s_font = SIDE / ((ft_strlen(s) + 4) * WIDTH_FONT);
	p.x = (SIDE / 2) - (WIDTH_FONT * env->s_font * ft_strlen(s) / 2);
	p.y = (SIDE / 10);
	random_handler_start(&p.x, &p.y, &s, random);
	env->editor.color_text = color;
	if (u[0] % 33 == 0)
		color += u[1] == 1 ? 0x110000 : -0x110000;
	u[1] = color == 0x330000 ? 1 : u[1];
	u[1] = color == 0xFF0000 ? 0 : u[1];
	display_sentence(env, s, p, color);
	env->s_font = random[3];
}

int			start(t_env *env)
{
	static int	pos;
	static int	option;
	int			i;

	i = -1;
	display_title(env);
	if (pos == 2 && env->keys[SDLK_KP_ENTER % 42] == ON && option != TRUE)
	{
		reverse((unsigned int *)&option);
		env->keys[SDLK_KP_ENTER % 42] = OFF;
	}
	else if (pos != 2 || env->keys[SDLK_LEFT % 42] == ON)
		option = FALSE;
	if (option == TRUE)
		options(env, &option);
	if (pos == 0 && env->keys[SDLK_KP_ENTER % 42] == ON)
		return (key_r(env));
	if (pos == 1 && env->keys[SDLK_KP_ENTER % 42] == ON)
		return (key_e(env));
	while (++i <= 2)
		display_start(env, pos, i);
	if (option == FALSE)
		check_key_start(env, &pos, 0, 2);
	display_instruction_start(env);
	return (SUCCESS);
}
