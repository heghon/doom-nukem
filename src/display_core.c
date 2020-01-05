/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 21:34:30 by sseneca           #+#    #+#             */
/*   Updated: 2019/12/09 20:41:46 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <math.h>
#include <pthread.h>
#include <unistd.h>

static void	choose_display_column(t_env *env, t_utils *u, t_texture *tex)
{
	if (!(u->a.sector < 0 || u->b.sector < 0))
	{
		if (env->rend.sector == u->a.sector && env->rend.p[u->screenx] == 0)
			prepare_floor_ceiling(env, u, 2);
		else if (env->rend.see == invisible && u->a.ceiling
			< (env->p.pos.z * 20) && env->rend.p[u->screenx] == 0)
			prepare_floor_ceiling(env, u, 0);
		else if (env->rend.see == invisible && u->a.floor > (env->p.pos.z * 20)
			&& env->rend.p[u->screenx] == 0)
			prepare_floor_ceiling(env, u, 1);
	}
	if (env->rend.see == visible && u->b.next_sector == -1
		&& env->rend.p[u->screenx] == 0)
	{
		if (u->a.floor == env->sector[env->rend.sector].floor
			&& u->a.ceiling == env->sector[env->rend.sector].ceiling)
			env->rend.w[u->screenx] = 1;
		draw_wall(u, (unsigned int *)env->view.layer[render_layer], tex);
	}
	else if (u->b.next_sector != -1)
	{
		env->rend.p[u->screenx] = 1;
		portal_handler(env, u, tex);
	}
}

static void	display_column(t_env *env, t_utils *u, t_texture *tex)
{
	t_float	p;
	t_float	in;
	float	angle;
	float	coeff;

	u->height = u->pente * u->screenx + u->k;
	angle = atan2(env->p.left.x, env->p.left.y)
		- (((2 * ANGLE_VISION) / SIDE) * u->screenx);
	u->old_end = (SIDE * env->p.cam) + (u->height * (env->p.pos.z))
		- u->height * (u->a.floor) / 20.0;
	u->height *= (u->a.ceiling - u->a.floor) / 20.0;
	u->start = u->old_end - u->height;
	u->end = u->old_end >= SIDE ? SIDE - 1 : u->old_end;
	p.x = sin(angle) + env->p.pos.x;
	p.y = cos(angle) + env->p.pos.y;
	in = inter_position_f(u->a.pos, u->b.pos, env->p.pos, p);
	coeff = pythagore4(in.x, (float)u->old_a.x, in.y, (float)u->old_a.y);
	u->coeff = coeff;
	coeff -= tex->size * ((int)coeff / (int)tex->size);
	u->w = tex->w * coeff / tex->size;
	if (u->a.sector == -1 && u->coeff != coeff)
		return ;
	u->w = u->w < 0 ? 0 : u->w;
	choose_display_column(env, u, tex);
}

void		*prepare_thread(void *struc)
{
	t_env	*env;
	int		thread;
	t_utils	*u;

	env = struc;
	thread = env->thread_i;
	u = &env->tmp[thread];
	if (++env->thread_i < NB_THREADS)
	{
		pthread_create(&env->thread[env->thread_i],
				NULL, prepare_thread, (void *)env);
	}
	while (++u->screenx < u->b.screenx)
	{
		if (u->screenx % NB_THREADS == thread)
			display_column(env, u, &env->texture[u->a.texture]);
	}
	pthread_exit(NULL);
}

static void	init_utils(t_env *env, t_utils *u, t_wall *a, t_wall *b)
{
	float	height[2];
	int		i;

	u->old_a = a->previous_pos;
	u->old_b = b->previous_pos;
	u->a = *a;
	u->b = *b;
	height[0] = u->a.dist <= 0 ? SIDE : SIDE / u->a.dist;
	height[1] = u->b.dist <= 0 ? SIDE : SIDE / u->b.dist;
	u->pente = (float)(height[1] - height[0]) / (b->screenx - a->screenx);
	u->k = -u->pente * u->a.screenx + height[0];
	u->screenx = u->a.screenx - 1;
	u->lum = env->sector[env->rend.sector].luminosity;
	i = -1;
	while (++i < env->sector[a->sector].num_walls)
	{
		u->corner.x = i == 0 || env->wall[env->sector[a->sector].start_wall
			+ i].pos.x < u->corner.x ? env->wall[env->sector
			[a->sector].start_wall + i].pos.x : u->corner.x;
		u->corner.y = i == 0 || env->wall[env->sector[a->sector].start_wall
			+ i].pos.y < u->corner.y ? env->wall[env->sector
			[a->sector].start_wall + i].pos.y : u->corner.y;
	}
}

void		display_wall(t_env *env, t_wall *a, t_wall *b)
{
	t_utils u;
	int		i;

	if (isnan(a->dist) || isnan(b->dist))
		return ;
	init_utils(env, &u, a, b);
	i = -1;
	if (!env->option.thread)
	{
		while (++u.screenx < u.b.screenx)
			display_column(env, &u, &env->texture[u.a.texture]);
		return ;
	}
	while (++i < NB_THREADS)
		env->tmp[i] = u;
	env->thread_i = 0;
	pthread_create(&env->thread[0], NULL, prepare_thread, (void *)env);
	i = -1;
	while (++i < NB_THREADS)
		if (pthread_join(env->thread[i], NULL))
			sleep(1);
}
