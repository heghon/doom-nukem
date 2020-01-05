/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:27:10 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/10 00:02:58 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <stdlib.h>

void			del_layer(t_env *env)
{
	free(env->view.layer[editor_layer]);
	free(env->view.layer[render_layer]);
	free(env->view.layer[menu_layer]);
}

void			del_render(t_env *env)
{
	free(env->rend.bunch[0]);
	free(env->rend.bunch[1]);
	free(env->rend.wall[0]);
	free(env->rend.wall[1]);
	free(env->rend.portal);
	env->rend.bunch[0] = NULL;
	env->rend.bunch[1] = NULL;
	env->rend.wall[0] = NULL;
	env->rend.wall[1] = NULL;
	env->rend.portal = NULL;
}

int				end_programme(t_env *env, char *msg)
{
	(void)msg;
	del_layer(env);
	del_render(env);
	SDL_DestroyTexture(env->screen);
	SDL_DestroyRenderer(env->render);
	SDL_DestroyWindow(env->win);
	SDL_Quit();
	free(env);
	return (ERROR);
}

int				main(int ac, char **av, char **envp)
{
	t_env		*env;
	int			ret;
	int			ret2;

	ret = SUCCESS;
	if (ac != 2)
		return (ERROR);
	env = ft_memalloc(sizeof(t_env));
	if (env == NULL)
		return (ERROR);
	env->envp = envp;
	env->file_name = av[1];
	ret = init_view(env);
	ret2 = malloc_render(env);
	if (ret == ERROR || ret2 == ERROR)
	{
		end_programme(env, "Fin anormale du programme\n");
		return (ERROR);
	}
	manage_program(env);
	init_game(env);
	run_game(env);
	end_programme(env, "Fin normale du programme\n");
	return (SUCCESS);
}
