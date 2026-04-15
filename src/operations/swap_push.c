/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:00:00 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 17:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

void	swap(t_stack *stack)
{
	int	tmp;

	if (!stack || stack->size < 2)
		return ;
	tmp = stack->top->value;
	stack->top->value = stack->top->next->value;
	stack->top->next->value = tmp;
	tmp = stack->top->index;
	stack->top->index = stack->top->next->index;
	stack->top->next->index = tmp;
}

void	sa(t_stack *a, t_ops *ops)
{
	swap(a);
	ops->sa++;
	write(1, "sa\n", 3);
}

void	sb(t_stack *b, t_ops *ops)
{
	swap(b);
	ops->sb++;
	write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b, t_ops *ops)
{
	swap(a);
	swap(b);
	ops->ss++;
	write(1, "ss\n", 3);
}

void	push(t_stack *src, t_stack *dest)
{
	t_node	*tmp;

	if (!src || !src->top)
		return ;
	tmp = src->top;
	src->top = src->top->next;
	tmp->next = dest->top;
	dest->top = tmp;
	src->size--;
	dest->size++;
}
