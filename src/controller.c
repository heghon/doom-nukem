/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 19:57:09 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/27 01:11:04 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				key_press(t_env *env)
{
	int			keycode;
	int			ret;

	ret = SUCCESS;
	keycode = env->event.key.keysym.sym;
	if (filter_keys(keycode) == TRUE)
		env->keys[keycode % 42] = ON;
	env->listen = press;
	if ((filter_pkeys(keycode) == TRUE) && env->p_keys[keycode % 100])
		ret = env->p_keys[keycode % 100](env);
	if (env->mode == mode_editor)
	{
		update_attribut(env);
		navigation_editor(env);
	}
	return (ret);
}

int				key_release(t_env *env)
{
	int			keycode;

	keycode = env->event.key.keysym.sym;
	if (filter_keys(keycode) == TRUE)
		env->keys[keycode % 42] = OFF;
	env->listen = release;
	return (SUCCESS);
}

int				mouse_press(t_env *env)
{
	int			keycode;

	keycode = env->event.button.button;
	env->keys[keycode % 42] = ON;
	env->listen = press;
	return (SUCCESS);
}

int				mouse_release(t_env *env)
{
	int			keycode;

	keycode = env->event.button.button;
	env->keys[keycode % 42] = OFF;
	env->listen = release;
	return (SUCCESS);
}

int				mouse_move(t_env *env)
{
	env->editor.old_cursor = env->editor.cursor;
	env->editor.cursor.x = env->event.motion.x;
	env->editor.cursor.y = env->event.motion.y;
	env->listen = move;
	point_to_grille(&env->editor.cursor);
	brush_color(env, BLACK);
	draw_line(&env->view, &env->editor.start_line, &env->editor.old_cursor);
	return (SUCCESS);
}
