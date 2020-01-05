/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:32:51 by mbenjell          #+#    #+#             */
/*   Updated: 2019/12/09 22:07:33 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <unistd.h>
#include <stdlib.h>

int				play_sound(t_env *env, char *audio_file)
{
	pid_t		pid;
	int			ret;
	static char *argv[] = {BIN_PLAYER_AUDIO, "", NULL};

	pid = fork();
	argv[1] = audio_file;
	if (pid == 0)
	{
		ret = execve(BIN_PLAYER_AUDIO, argv, env->envp);
		exit(SUCCESS);
	}
	return (pid);
}
