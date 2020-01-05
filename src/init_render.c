/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgavillo <mgavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 23:56:57 by mgavillo          #+#    #+#             */
/*   Updated: 2019/12/09 21:00:46 by mgavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			malloc_render(t_env *env)
{
	env->rend.all = NB_WALLS + (NB_OBJECTS + NB_CHARACTERS) * 2;
	env->rend.bunch[0] = (t_bunch*)ft_memalloc(sizeof(t_bunch)
												* (env->rend.all + 1));
	env->rend.bunch[1] = (t_bunch*)ft_memalloc(sizeof(t_bunch)
												* (env->rend.all + 1));
	env->rend.wall[0] = (t_w*)ft_memalloc(sizeof(t_w)
												* (env->rend.all + 1));
	env->rend.wall[1] = (t_w*)ft_memalloc(sizeof(t_w)
												* (env->rend.all + 1));
	env->rend.portal = (t_portal*)ft_memalloc(sizeof(t_portal)
												* (env->rend.all + 1));
	if (!(env->rend.bunch[0] && env->rend.bunch[1] && env->rend.wall[0]
			&& env->rend.wall[1] && env->rend.portal))
		return (ERROR);
	env->rend.bunch[0][env->rend.all].next = -1;
	env->rend.bunch[1][env->rend.all].next = -1;
	env->rend.wall[0][env->rend.all].next = -1;
	env->rend.wall[1][env->rend.all].next = -1;
	env->rend.portal[env->rend.all].next = -1;
	env->rend.first_portal = env->rend.all;
	return (SUCCESS);
}

int			init_render(t_env *env)
{
	int i;

	i = -1;
	struct_direction(env);
	env->rend.first_bunch[visible] = -1;
	env->rend.cur[visible][e_b] = -1;
	env->rend.cur[visible][e_w] = -1;
	env->rend.first_bunch[invisible] = -1;
	env->rend.cur[invisible][e_b] = -1;
	env->rend.cur[invisible][e_w] = -1;
	while (i++ < env->card[e_wall])
		screen_x(env, &env->wall[i]);
	return (SUCCESS);
}

static void	render_portal(t_env *env)
{
	int i;

	env->p.pos = env->rend.portal[env->rend.first_portal].pos;
	env->p.dir = env->rend.portal[env->rend.first_portal].dir;
	new_cord(env);
	init_fov(env);
	env->rend.i = env->rend.portal[env->rend.first_portal].i;
	env->rend.j = env->rend.portal[env->rend.first_portal].j;
	i = env->rend.portal[env->rend.first_portal].i.screenx - 1;
	while (i < 0)
		i++;
	while (++i <= env->rend.portal[env->rend.first_portal].j.screenx
														&& i < SIDE)
		env->rend.p[i] = 0;
	env->rend.sector = env->rend.portal[env->rend.first_portal].j.next_sector;
	env->rend.port = ON;
}

static void	render_scene(t_env *env)
{
	int i;

	i = -1;
	while (++i < SIDE)
	{
		env->rend.p[i] = 0;
		env->rend.w[i] = 0;
	}
	ft_memset(env->view.layer[render_layer], 0, SIDE * SIDE * 4);
	env->p.tmp_dir = env->p.dir;
	env->p.tmp_pos = env->p.pos;
	env->rend.port = OFF;
	env->rend.euc = OFF;
	env->rend.cur[0][e_portal] = -1;
	env->rend.i.screenx = 0;
	env->rend.j.screenx = SIDE;
	env->p.sector = in_which_sector(env);
	env->rend.sector = env->p.sector;
	init_render(env);
}

int			render(t_env *env)
{
	static int nb_port = 0;

	if (env->rend.first_portal != env->rend.all && env->rend.first_portal != -1)
	{
		nb_port++;
		if (nb_port > 20)
		{
			env->rend.first_portal = env->rend.all;
			return (choose_sector);
		}
		render_portal(env);
	}
	else
	{
		nb_port = 0;
		render_scene(env);
	}
	create_bunch(env);
	return (choose_sector);
}
