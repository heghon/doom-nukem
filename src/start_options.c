/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseneca <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 06:08:55 by sseneca           #+#    #+#             */
/*   Updated: 2019/12/01 06:08:56 by sseneca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		display_instruction_start(t_env *env)
{
	static int	move;
	static int	cc = 1;
	static int	frame;
	static int	color;
	t_point		p;

	if (env->keys[SDLK_DOWN % 42] == ON
		|| env->keys[SDLK_UP % 42] == ON
		|| env->keys[SDLK_KP_ENTER % 42] == ON)
		move++;
	if (move < 42)
	{
		env->editor.color_text = frame > 0 ? color : 0;
		frame++;
		cc = env->editor.color_text == 0xFFFFFF ? 1 : cc;
		cc = env->editor.color_text == 0 ? 0 : cc;
		if (frame % 20 == 0)
			env->editor.color_text += cc == 0 ? 0x111111 : -0x111111;
		p.x = (SIDE / 2) - (WIDTH_FONT * env->s_font * 29 / 2);
		p.y = SIDE / 4;
		display_text(env, p, "use enter and the arrows here;"
		"you can use the mouse in game");
		color = env->editor.color_text;
	}
}

static void	display_option_row(t_env *env, int c, char *s, int ooi)
{
	t_point		p[4];
	int			here;
	char		*on_off;

	here = c % 2 == 1 ? 1 : 0;
	c /= 2;
	if (c != 0)
		on_off = ooi == 0 ? "off" : "on";
	p[0].x = SIDE * 0.59;
	p[0].y = SIDE / 18 * (12 + c);
	p[1].x = SIDE * 0.8;
	p[1].y = SIDE / 18 * (12 + c);
	display_box(env, p, SIDE / 18 * (12 + c), here);
	p[0].x = SIDE * 0.6;
	p[0].y = SIDE / 18 * (12 + c) + (HEIGHT_FONT * env->s_font / 2);
	display_text(env, p[0], s);
	p[0].x = SIDE * 0.75;
	env->editor.color_text = 0;
	if (c == 0)
		display_value(env, p[0], ooi);
	else
		display_text(env, p[0], on_off);
}

static void	update_options(t_env *env, int pos)
{
	static int	ret;
	static int	rev;

	if (env->keys[SDLK_KP_ENTER % 42] == ON && ret == 0)
		ret = 1;
	else if (env->keys[SDLK_KP_ENTER % 42] == OFF)
	{
		ret = 0;
		rev = 0;
	}
	if (ret == 1 && rev == 0)
	{
		if (pos == 0)
			manage_level(&env->p, env->nb_level);
		else if (pos == 1)
			reverse(&env->option.editor);
		else if (pos == 2)
			reverse(&env->option.thread);
		rev = 1;
	}
}

static void	check_key_options(t_env *env, int *pos, int min, int max)
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
	update_options(env, *pos);
}

void		options(t_env *env, int *option)
{
	static int	pos;
	int			color;

	color = env->editor.color_text;
	env->editor.color_text = pos == 0 ? 0xAA0000 : 0;
	display_option_row(env, 0 + (pos == 0 ? 1 : 0),
			"level", env->p.new_level);
	env->editor.color_text = pos == 1 ? 0xAA0000 : 0;
	display_option_row(env, 2 + (pos == 1 ? 1 : 0),
			"editor", env->option.editor);
	env->editor.color_text = pos == 2 ? 0xAA0000 : 0;
	display_option_row(env, 4 + (pos == 2 ? 1 : 0),
			"thread", env->option.thread);
	env->editor.color_text = color;
	check_key_options(env, &pos, -1, 2);
	if (pos == -1)
	{
		*option = FALSE;
		pos = 0;
	}
}
