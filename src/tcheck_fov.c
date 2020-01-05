/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcheck_fov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:15:37 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/07 02:03:31 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		init_fov(t_env *env)
{
	env->p.left.x = env->p.dir.x * cos(-ANGLE_VISION)
									- env->p.dir.y * sin(-ANGLE_VISION);
	env->p.left.y = env->p.dir.x * sin(-ANGLE_VISION)
									+ env->p.dir.y * cos(-ANGLE_VISION);
	env->p.right.x = env->p.dir.x * cos(ANGLE_VISION)
									- env->p.dir.y * sin(ANGLE_VISION);
	env->p.right.y = env->p.dir.x * sin(ANGLE_VISION)
									+ env->p.dir.y * cos(ANGLE_VISION);
}

static int	in_fov(t_player *p, t_point point)
{
	t_float vec;

	vec.x = point.x - p->pos.x;
	vec.y = point.y - p->pos.y;
	if (p->left.y * vec.x - p->left.x * vec.y <= 0
			&& p->right.y * vec.x - p->right.x * vec.y >= 0)
		return (TRUE);
	return (FALSE);
}

int			tcheck_fov(t_env *env, t_point a, t_point b)
{
	t_float left;
	t_float	right;

	left.x = env->p.pos.x + env->p.left.x * SIDE * 2;
	left.y = env->p.pos.y + env->p.left.y * SIDE * 2;
	right.x = env->p.pos.x + env->p.right.x * SIDE * 2;
	right.y = env->p.pos.y + env->p.right.y * SIDE * 2;
	if (in_fov(&env->p, a) || in_fov(&env->p, b))
		return (1);
	if (segment_inter_f(a, b, env->p.pos, left))
		return (1);
	if (segment_inter_f(a, b, env->p.pos, right))
		return (1);
	return (0);
}

int			is_in_range(t_env *env, t_wall i, t_wall j)
{
	if ((i.screenx >= env->rend.i.screenx
			&& i.screenx <= env->rend.j.screenx)
			|| (j.screenx >= env->rend.i.screenx
			&& j.screenx <= env->rend.j.screenx)
			|| tcheck_fov(env, i.pos, j.pos))
		return (TRUE);
	return (FALSE);
}
