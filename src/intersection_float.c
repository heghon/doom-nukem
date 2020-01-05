/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_float.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 10:24:15 by sseneca           #+#    #+#             */
/*   Updated: 2019/12/03 21:41:25 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	onsegment_f2(t_float p, t_point q, t_float r)
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

int			onsegment_f(t_point p, t_float q, t_point r)
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

static int	orientation_f2(t_float p, t_float q, t_point r)
{
	int val;

	val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return (0);
	return (val > 0 ? 1 : 2);
}

static int	orientation_f(t_point p, t_point q, t_float r)
{
	int val;

	val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0)
		return (0);
	return (val > 0 ? 1 : 2);
}

int			segment_inter_f(t_point a, t_point b, t_float c, t_float d)
{
	int o[4];

	o[0] = orientation_f(a, b, c);
	o[1] = orientation_f(a, b, d);
	o[2] = orientation_f2(c, d, a);
	o[3] = orientation_f2(c, d, b);
	if (o[0] != o[1] && o[2] != o[3])
		return (1);
	if (o[0] == 0 && onsegment_f(a, c, b))
		return (1);
	if (o[1] == 0 && onsegment_f(a, d, b))
		return (1);
	if (o[2] == 0 && onsegment_f2(c, a, d))
		return (1);
	if (o[3] == 0 && onsegment_f2(c, b, d))
		return (1);
	return (0);
}
