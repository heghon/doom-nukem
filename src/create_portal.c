/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_portal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 00:09:23 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/09 20:37:24 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	good_portal(t_env *env, int j, int k)
{
	int i;
	int nb;

	nb = 0;
	i = env->rend.wall[0][j].w.screenx;
	while (i++ < env->rend.wall[0][k].w.screenx)
	{
		if (env->rend.p[i] != 1 && env->rend.w[i] != 1)
			return (TRUE);
	}
	return (FALSE);
}

static void	add_portal_after(t_env *env)
{
	int	p;
	int	tmp;

	p = env->rend.first_portal;
	while (env->rend.portal[p].sector != env->rend.sector && p != env->rend.all)
		p = env->rend.portal[p].next;
	if (p == env->rend.all)
	{
		env->rend.portal[env->rend.cur[0]
			[e_portal]].next = env->rend.cur[0][e_portal] + 1;
		env->rend.portal[env->rend.cur[0][e_portal] + 1].next = env->rend.all;
	}
	else
	{
		tmp = env->rend.portal[p].next;
		env->rend.portal[p].next = env->rend.cur[0][e_portal] + 1;
		env->rend.portal[env->rend.cur[0][e_portal] + 1].next = tmp;
	}
}

void		add_portal(t_env *env, int j, int k)
{
	if (env->rend.wall[0][k].w.next_sector
			!= env->rend.sector && good_portal(env, j, k))
	{
		if (env->rend.cur[0][e_portal] == -1
			|| env->rend.first_portal == env->rend.all
			|| env->rend.first_portal == -1)
		{
			env->rend.first_portal = env->rend.cur[0][e_portal] + 1;
			env->rend.portal[env->rend.cur[0]
									[e_portal] + 1].next = env->rend.all;
		}
		else
			add_portal_after(env);
		env->rend.cur[0][e_portal]++;
		env->rend.portal[env->rend.cur[0][e_portal]].i = env->rend.wall[0][j].w;
		env->rend.portal[env->rend.cur[0][e_portal]].j = env->rend.wall[0][k].w;
		env->rend.portal[env->rend.cur[0][e_portal]].sector = env->rend.portal
									[env->rend.cur[0][e_portal]].j.next_sector;
		env->rend.portal[env->rend.cur[0][e_portal]].pos = env->p.pos;
		env->rend.portal[env->rend.cur[0][e_portal]].dir = env->p.dir;
	}
}
