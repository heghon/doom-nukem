/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_xbn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 02:54:33 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/19 11:38:10 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		key_alt(t_env *env)
{
	if (env->mode == mode_game)
		crouch_handler(env);
	return (SUCCESS);
}

int		key_lctrl(t_env *env)
{
	if (env->mode == mode_game)
		fly_handler(env);
	return (SUCCESS);
}

int		key_escape(t_env *env)
{
	if (env->mode != mode_start)
	{
		clear_layer(&env->view, menu_layer);
		env->mode = mode_start;
		return (SUCCESS);
	}
	return (END);
}

int		key_n(t_env *env)
{
	int	select;

	select = env->editor.select_mode;
	if (env->card[select] == 0)
		return (ERROR);
	if (env->mode == mode_editor)
		env->editor.select[select] = (env->editor.select[select] + 1)
										% env->card[select];
	centering(env);
	return (SUCCESS);
}

int		key_b(t_env *env)
{
	int	select;

	select = env->editor.select_mode;
	if (env->card[select] == 0)
		return (ERROR);
	if (env->mode == mode_editor)
	{
		if (env->editor.select[select] == 0)
			env->editor.select[select] = env->card[select] - 1;
		else
			env->editor.select[select]--;
	}
	centering(env);
	return (SUCCESS);
}
