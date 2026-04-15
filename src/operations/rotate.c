/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:00:00 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 17:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

void	rotate(t_stack *stack)
{
	t_node	*first;
	t_node	*tmp;

	if (!stack || stack->size < 2)
		return ;
	first = stack->top;
	stack->top = first->next;
	tmp = stack->top;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = first;
	first->next = NULL;
}

void	ra(t_stack *a, t_ops *ops)
{
	rotate(a);
	ops->ra++;
	write(1, "ra\n", 3);
}

void	rb(t_stack *b, t_ops *ops)
{
	rotate(b);
	ops->rb++;
	write(1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b, t_ops *ops)
{
	rotate(a);
	rotate(b);
	ops->rr++;
	write(1, "rr\n", 3);
}
