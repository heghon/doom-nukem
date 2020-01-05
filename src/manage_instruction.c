/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_instruction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 19:43:25 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:40:12 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		load_value(t_action *action, int *op1, int *op2)
{
	int			*vm;

	vm = action->mini_vm;
	*op1 = vm[action->pc + 2];
	*op1 = action->registre[*op1];
	if (vm[action->pc + INSTRUCTION_SIZE - 1] == TRUE)
		*op2 = vm[action->pc + 3];
	else
	{
		*op2 = vm[action->pc + 3];
		*op2 = action->registre[*op2];
	}
	return (SUCCESS);
}

void			manage_instr(t_env *env, t_action *action, int *vm)
{
	int			res;
	int			op1;
	int			op2;

	res = -99999;
	load_value(action, &op1, &op2);
	if (vm[action->pc] == e_if)
	{
		res = vm[action->pc + 1];
		res = action->registre[res];
		if (res == op1)
			action->pc += INSTRUCTION_SIZE;
		else
		{
			action->pc += INSTRUCTION_SIZE;
			action->pc += op2 * INSTRUCTION_SIZE;
		}
		return ;
	}
	if (vm[action->pc] < NB_INSTRUCTIONS)
		res = (env->do_op[vm[action->pc]])(op1, op2);
	action->registre[vm[action->pc + 1]] = res;
	action->pc += INSTRUCTION_SIZE;
}

int				read_instruction(t_env *env, int actor)
{
	t_action	*action;
	int			*vm;

	action = &env->action[actor];
	vm = action->mini_vm;
	action->pc = 0;
	while (action->pc < action->size_code)
		manage_instr(env, action, vm);
	return (SUCCESS);
}

int				manage_op(t_env *env)
{
	env->do_op[e_add] = addition;
	env->do_op[e_sub] = soustraction;
	env->do_op[e_mul] = multiplication;
	env->do_op[e_div] = division;
	env->do_op[e_cmp] = compare;
	return (SUCCESS);
}
