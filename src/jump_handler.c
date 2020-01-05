/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmenant <bmenant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 11:37:01 by bmenant           #+#    #+#             */
/*   Updated: 2019/12/09 23:48:37 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	jump_handler(t_env *e)
{
	if (e->p.state == stand)
	{
		e->jump_force = JUMP_FORCE;
		e->p.state = jump;
	}
	return (SUCCESS);
}

int	fly_handler(t_env *e)
{
	if ((e->p.state == stand || e->p.state == jump) && e->p.wings != 0)
	{
		e->fly_force = FLY_FORCE;
		e->p.state = fly;
	}
	else if (e->p.state == fly)
		e->p.state = stand;
	return (SUCCESS);
}

int	crouch_handler(t_env *e)
{
	if (e->p.state == stand)
	{
		e->p.pos.z -= 0.2;
		e->p.state = crouch;
	}
	else if (e->p.state == crouch)
	{
		e->p.pos.z += 0.2;
		e->p.state = stand;
	}
	return (SUCCESS);
}
