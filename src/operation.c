/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenjell <mbenjell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:57:58 by mbenjell          #+#    #+#             */
/*   Updated: 2019/11/17 02:43:48 by mbenjell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		addition(int op1, int op2)
{
	return (op1 + op2);
}

int		soustraction(int op1, int op2)
{
	return (op1 - op2);
}

int		multiplication(int op1, int op2)
{
	return (op1 * op2);
}

int		division(int op1, int op2)
{
	if (op2 == 0)
		return (op1);
	return (op1 / op2);
}

int		compare(int op1, int op2)
{
	return (op1 == op2);
}
