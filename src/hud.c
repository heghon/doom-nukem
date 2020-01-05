/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseneca <sseneca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 23:05:01 by sseneca           #+#    #+#             */
/*   Updated: 2019/12/09 23:49:34 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "../include/SDL.h"

unsigned int	adapt_luminosity(unsigned int hexa, float l)
{
	unsigned int	integer;
	unsigned int	h[3];

	integer = (hexa / 65536);
	h[0] = integer * l;
	h[0] = h[0] == 0 && integer != 0 ? 1 : h[0];
	hexa -= integer * 65536;
	integer = (hexa / 256);
	h[1] = integer * l;
	h[1] = h[1] == 0 && integer != 0 ? 1 : h[1];
	hexa -= integer * 256;
	h[2] = hexa * l;
	h[2] = h[2] == 0 && hexa != 0 ? 1 : h[2];
	return (h[0] * 65536 + h[1] * 256 + h[2]);
}

void			display_sentence(t_env *env, char *str,
									t_point p, unsigned int color)
{
	p.y += env->s_font * HEIGHT_FONT;
	env->editor.color_text = 0;
	display_text(env, p, str);
	p.y += 4;
	display_text(env, p, str);
	p.y -= 3;
	p.x -= 3;
	display_text(env, p, str);
	p.x += 5;
	p.x -= 3;
	env->editor.color_text = color;
	display_text(env, p, str);
}

static void		display_level(t_env *env)
{
	t_point	p;
	int		color;

	color = env->editor.color_text;
	env->editor.color_text = 0;
	p.y = SIDE / 48;
	p.x = SIDE - (SIDE / 30);
	display_value(env, p, env->p.current_level);
	p.y += (HEIGHT_NUM - HEIGHT_FONT) * env->s_font;
	p.x -= (WIDTH_FONT * env->s_font * 7);
	display_text(env, p, "level");
	env->editor.color_text = color;
	display_sentence(env, env->sentence[env->current_sentence].str,
		env->sentence[env->current_sentence].p,
		env->sentence[env->current_sentence].color);
}

static void		display_timer(t_env *env, t_player *player)
{
	t_point		p;
	int			color;
	static int	b;

	color = env->editor.color_text;
	p.x = WIDTH_NUM * env->s_font * 3;
	p.y = SIDE / 48;
	env->editor.color_text = 0xAA0000;
	player->total_time = (int)(SDL_GetTicks() / 1000);
	if (player->total_time >= player->timer)
		player->timer = player->total_time;
	else
		b = 1;
	if (env->hud.timer)
	{
		display_value(env, p, player->timer - player->total_time);
		if (b == 1 && player->total_time >= player->timer)
		{
			b = 0;
			player->current_level--;
		}
	}
	else
		b = 0;
	env->editor.color_text = color;
}

void			display_hud(t_env *env, t_hud *hud)
{
	int i;
	int inv;

	i = -1;
	inv = 0;
	if (env->sector[env->p.sector].light == 1)
		change_luminosity(&env->sector[env->p.sector]);
	choose_sentence(env);
	check_object(env, hud);
	if (env->hud.compass)
		display_compass(env, env->sector[env->p.sector].luminosity);
	while (++i < (int)hud->nb_inventory && i < 8)
	{
		env->view.color = adapt_luminosity(0x666666,
			env->sector[env->p.sector].luminosity);
		if (env->texture[env->object[hud->inventory[i]].a.texture].size == 1)
			inv++;
		else
			display_inventory(env, i - inv,
			env->object[hud->inventory[i]].a.texture,
			env->sector[env->p.sector].luminosity);
	}
	display_timer(env, &env->p);
	display_level(env);
}
