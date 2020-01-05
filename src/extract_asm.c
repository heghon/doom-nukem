/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_asm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 01:29:20 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:33:51 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				extract_instruction(t_stream *s)
{
	char		buff[42];

	stream_to_buff(s, buff);
	skip_space(s);
	if (ft_strequ(buff, "add") == TRUE)
		return (e_add);
	else if (ft_strequ(buff, "sub") == TRUE)
		return (e_sub);
	else if (ft_strequ(buff, "mul") == TRUE)
		return (e_mul);
	else if (ft_strequ(buff, "div") == TRUE)
		return (e_div);
	else if (ft_strequ(buff, "cmp") == TRUE)
		return (e_cmp);
	else if (ft_strequ(buff, "if") == TRUE)
		return (e_if);
	else
		return (ERROR);
}

int				extract_asm(t_env *env, int type_actor)
{
	int			nb;
	int			op;
	int			i;

	i = 0;
	nb = get_val(&env->stream, 0, VM_SIZE / INSTRUCTION_SIZE + 1);
	env->action[type_actor].size_code = nb * INSTRUCTION_SIZE;
	while (nb--)
	{
		if ((op = extract_instruction(&env->stream)) == ERROR)
			return (ERROR);
		env->action[type_actor].mini_vm[i++] = op;
		i = fill_vm(env, type_actor, i);
	}
	return (SUCCESS);
}
