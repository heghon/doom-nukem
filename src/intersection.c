/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 20:00:52 by sseneca           #+#    #+#             */
/*   Updated: 2019/12/03 21:41:42 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_float		inter_position_f(t_point a, t_point b, t_float c, t_float d)
{
	float	ab;
	float	data[3];
	float	abpos;
	t_float	inter;

	b.x -= a.x;
	b.y -= a.y;
	c.x -= a.x;
	c.y -= a.y;
	d.x -= a.x;
	d.y -= a.y;
	ab = sqrt(b.x * b.x + b.y * b.y) + 0.00000001;
	data[0] = b.x / ab;
	data[1] = b.y / ab;
	data[2] = c.x * data[0] + c.y * data[1];
	c.y = c.y * data[0] - c.x * data[1];
	c.x = data[2];
	data[2] = d.x * data[0] + d.y * data[1];
	d.y = d.y * data[0] - d.x * data[1];
	d.x = data[2];
	abpos = d.x + (c.x - d.x) * d.y / (d.y - c.y + 0.00000001);
	inter.x = a.x + abpos * data[0];
	inter.y = a.y + abpos * data[1];
	return (inter);
}

int			onsegment(t_point p, t_point q, t_point r)
{
	int	max[2];
	int	min[2];

	max[0] = p.x >= r.x ? p.x : r.x;
	min[0] = p.x >= r.x ? r.x : p.x;
	max[1] = p.y >= r.y ? p.y : r.y;
	min[1] = p.y >= r.y ? r.y : p.y;
	if (q.x <= max[0] && q.x >= min[0] && q.y <= max[1] && q.y >= min[1])
		return (1);
	return (0);
}

static int	orientation(t_point p, t_point q, t_point r)
{
	int val;

	val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return (0);
	return (val > 0 ? 1 : 2);
}

int			segment_inter(t_point a, t_point b, t_point c, t_point d)
{
	int o[4];

	o[0] = orientation(a, b, c);
	o[1] = orientation(a, b, d);
	o[2] = orientation(c, d, a);
	o[3] = orientation(c, d, b);
	if (o[0] != o[1] && o[2] != o[3])
		return (1);
	if (o[0] == 0 && onsegment(a, c, b))
		return (1);
	if (o[1] == 0 && onsegment(a, d, b))
		return (1);
	if (o[2] == 0 && onsegment(c, a, d))
		return (1);
	if (o[3] == 0 && onsegment(c, b, d))
		return (1);
	return (0);
}
