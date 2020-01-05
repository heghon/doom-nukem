/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 01:29:20 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:29:32 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			add_object(t_env *env)
{
	t_point	obj_pos;

	if (available_memory(env, e_object) == FALSE)
		return (ERROR);
	obj_pos = env->editor.cursor;
	reverse_translate(env->editor.direction, &obj_pos);
	env->object[env->card[e_object]].pos = obj_pos;
	env->object[env->card[e_object]].color = GREEN;
	env->card[e_object]++;
	return (SUCCESS);
}
