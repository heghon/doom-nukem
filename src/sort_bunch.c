/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bunch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:29:20 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/10 00:08:33 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	add_closest(t_env *env, int min[2], int head)
{
	int v;

	v = env->rend.see;
	if (min[0] != head)
	{
		env->rend.bunch[v][min[0]].next = env->rend.bunch[v][min[1]].next;
		if (head == -1)
		{
			env->rend.bunch[v][min[1]].next = env->rend.first_bunch[v];
			env->rend.first_bunch[v] = min[1];
		}
		else
		{
			env->rend.bunch[v][min[1]].next = env->rend.bunch[v][head].next;
			env->rend.bunch[v][head].next = min[1];
		}
	}
	return (min[1]);
}

static void	test_closest(t_env *env, int *min, int *min1, int head)
{
	int	previous;
	int	i;

	if (head != -1)
	{
		*min1 = env->rend.bunch[env->rend.see][head].next;
		i = env->rend.bunch[env->rend.see][*min1].next;
	}
	else
		i = env->rend.bunch[env->rend.see][*min1].next;
	previous = *min1;
	*min = head;
	while (i != -1 && i != env->rend.all)
	{
		if (!closest_bunch1(env, *min1, i) && i != *min1)
		{
			*min = previous;
			*min1 = i;
		}
		previous = i;
		i = env->rend.bunch[env->rend.see][i].next;
		if (i == *min1)
			i = env->rend.bunch[env->rend.see][i].next;
	}
}

void		sort_bunch(t_env *env)
{
	int min[2];
	int	head;
	int	v;

	v = env->rend.see;
	head = -1;
	min[1] = env->rend.first_bunch[v];
	if (min[1] != -1)
	{
		while (head == -1 || env->rend.bunch[v][head].next != env->rend.all)
		{
			test_closest(env, &min[0], &min[1], head);
			head = add_closest(env, min, head);
		}
	}
	if (env->rend.see == invisible)
	{
		env->rend.see = visible;
		sort_bunch(env);
		return ;
	}
	sort_bunch_inv(env);
	display_sector(env);
}
