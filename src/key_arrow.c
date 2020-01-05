/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_arrow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 02:53:13 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/19 11:29:23 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		key_up(t_env *env)
{
	if (env->mode == mode_editor)
	{
		if (env->editor.select_mode > 0)
			env->editor.select_mode--;
		centering(env);
	}
	return (SUCCESS);
}

int		key_down(t_env *env)
{
	if (env->mode == mode_editor)
	{
		if (env->editor.select_mode < e_character)
			env->editor.select_mode++;
		centering(env);
	}
	return (SUCCESS);
}

int		key_space(t_env *env)
{
	if (env->mode == mode_game)
		jump_handler(env);
	return (SUCCESS);
}

int		key_left(t_env *env)
{
	if (env->mode == mode_editor)
	{
		select_attribut(env, 0);
		update_attribut(env);
	}
	return (SUCCESS);
}

int		key_right(t_env *env)
{
	if (env->mode == mode_editor)
	{
		select_attribut(env, 1);
		update_attribut(env);
	}
	return (SUCCESS);
}
