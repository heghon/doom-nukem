/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 14:08:06 by bmenant           #+#    #+#             */
/*   Updated: 2019/12/09 21:13:57 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <math.h>

int				int_seg_seg(t_float p1, t_float p2, t_float p3, t_float p4)
{
	t_float v1;
	t_float v2;
	t_float v3;

	v1.x = p2.x - p1.x;
	v1.y = p2.y - p1.y;
	v2.x = p3.x - p1.x;
	v2.y = p3.y - p1.y;
	v3.x = p4.x - p1.x;
	v3.y = p4.y - p1.y;
	if ((v1.x * v3.y - v1.y * v3.x) * (v1.x * v2.y - v1.y * v2.x) <= 0)
	{
		v1.x = p4.x - p3.x;
		v1.y = p4.y - p3.y;
		v2.x = p1.x - p3.x;
		v2.y = p1.y - p3.y;
		v3.x = p2.x - p3.x;
		v3.y = p2.y - p3.y;
		if ((v1.x * v3.y - v1.y * v3.x) * (v1.x * v2.y - v1.y * v2.x) <= 0)
			return (TRUE);
	}
	return (FALSE);
}

int				int_circle_point(t_float p, t_float pc, int ray)
{
	float	d2;

	d2 = (p.x - pc.x) * (p.x - pc.x) + (p.y - pc.y) * (p.y - pc.y);
	if (d2 > (float)ray * (float)ray)
		return (FALSE);
	return (TRUE);
}

int				int_circle_line(t_float pc, int ray, t_float p3, t_float p4)
{
	t_float a;
	t_float b;
	float	num;
	float	den;

	a.x = p4.x - p3.x;
	a.y = p4.y - p3.y;
	b.x = pc.x - p3.x;
	b.y = pc.y - p3.y;
	num = (a.x * b.y) - (a.y * b.x);
	num *= (num < 0 ? -1 : 1);
	den = sqrt(a.x * a.x + a.y * a.y);
	if (num / den < (float)ray)
		return (TRUE);
	return (FALSE);
}

int				int_circle_seg(t_float pc, int ray, t_float p3, t_float p4)
{
	t_float ab;
	t_float ac;
	t_float bc;

	if (int_circle_line(pc, ray, p3, p4) == FALSE)
		return (FALSE);
	ab.x = p4.x - p3.x;
	ab.y = p4.y - p3.y;
	ac.x = pc.x - p3.x;
	ac.y = pc.y - p3.y;
	bc.x = pc.x - p4.x;
	bc.y = pc.y - p4.y;
	if ((ab.x * ac.x + ab.y * ac.y >= 0 && -ab.x * bc.x - ab.y * bc.y >= 0)
			|| int_circle_point(p3, pc, ray) || int_circle_point(p4, pc, ray))
		return (TRUE);
	return (FALSE);
}
