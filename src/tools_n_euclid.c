/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_n_euclid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:03:51 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/09 23:57:52 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

float	ft_angle(t_float a, t_float b)
{
	float	dot;
	float	angle;

	dot = a.x * b.x + a.y * b.y;
	angle = acos((float)(dot
		/ (sqrt((a.x * a.x) + (a.y * a.y)) * sqrt((b.x * b.x) + (b.y * b.y)))));
	if (a.y * b.x - a.x * b.y < 0)
		angle *= -1;
	return (angle);
}

t_float	find_portal(t_env *e, int s[2], int *k, int *l)
{
	int		i;
	int		end;
	int		j;
	t_float	vec;

	vec.x = 0;
	vec.y = 0;
	end = e->sector[s[0]].start_wall + e->sector[s[0]].num_walls - 1;
	j = end;
	while (j >= e->sector[s[0]].start_wall)
	{
		i = (j == e->sector[s[0]].start_wall) ? end : j - 1;
		if (e->wall[i].next_sector == s[1])
		{
			vec.x = e->wall[i].pos.x - e->wall[j].pos.x;
			vec.y = e->wall[i].pos.y - e->wall[j].pos.y;
			*k = i;
			*l = j;
			return (vec);
		}
		j--;
	}
	*k = 0;
	*l = 0;
	return (vec);
}

void	line_cercle_inter(t_env *env, float p[2], t_float center, int port[2])
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	k;

	k = center.y - (p[0] * center.x);
	a = 1 + (p[0] * p[0]);
	b = (-2 * center.x) + (2 * p[0] * k) - (2 * p[0] * center.y);
	c = (center.x * center.x) + (k * k)
			- (2 * center.y * k) + (center.y * center.y) - (p[1] * p[1]);
	delta = (b * b) - (4 * a * c);
	if (delta > 0)
		env->p.pos.x = (float)(-b + sqrt(delta)) / (2 * a);
	env->p.pos.y = (p[0] * env->p.pos.x) + k;
	if (left_to_right(&env->p, env->wall[port[0]].pos, env->wall[port[1]].pos))
		return ;
	env->p.pos.x = (float)(-b - sqrt(delta)) / (2 * a);
	env->p.pos.y = p[0] * env->p.pos.x + k;
}

t_float	same_xy_dist(t_env *env, t_wall i, t_wall j)
{
	t_float	perp;

	perp.x = 0;
	perp.y = 0;
	if (i.previous_pos.y - j.previous_pos.y == 0)
	{
		perp.x = env->p.pos.x;
		perp.y = i.previous_pos.y;
	}
	if (i.previous_pos.x - j.previous_pos.x == 0)
	{
		perp.x = i.previous_pos.x;
		perp.y = env->p.pos.y;
	}
	return (perp);
}

float	calc_dist(t_env *env, t_float *perp, t_wall i, t_wall j)
{
	float	coeff;
	float	coeff1;
	float	b;
	float	b1;

	if (i.previous_pos.x - j.previous_pos.x
				&& i.previous_pos.y - j.previous_pos.y)
	{
		coeff = (float)(i.previous_pos.y - j.previous_pos.y)
			/ (i.previous_pos.x - j.previous_pos.x);
		b = i.previous_pos.y - (((float)(i.previous_pos.y - j.previous_pos.y)
			/ (i.previous_pos.x - j.previous_pos.x)) * i.previous_pos.x);
		coeff1 = (float)-1 / coeff;
		b1 = env->p.pos.y - (float)(coeff1 * env->p.pos.x);
		if ((coeff - coeff1) != 0)
			perp->x = (float)(b1 - b) / (coeff - coeff1);
		else
			perp->x = b1;
		perp->y = perp->x * coeff + b;
	}
	else
		*perp = same_xy_dist(env, i, j);
	return (sqrt(((perp->x - env->p.pos.x) * (perp->x - env->p.pos.x)) +
		((perp->y - env->p.pos.y) * (perp->y - env->p.pos.y))));
}
