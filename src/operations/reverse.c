/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:00:00 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 17:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

void	reverse_rotate(t_stack *stack)
{
	t_node	*prev;
	t_node	*tmp;

	if (!stack || stack->size < 2)
		return ;
	prev = NULL;
	tmp = stack->top;
	while (tmp->next)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = NULL;
	tmp->next = stack->top;
	stack->top = tmp;
}

void	rra(t_stack *a, t_ops *ops)
{
	reverse_rotate(a);
	ops->rra++;
	write(1, "rra\n", 4);
}

void	rrb(t_stack *b, t_ops *ops)
{
	reverse_rotate(b);
	ops->rrb++;
	write(1, "rrb\n", 4);
}

void	rrr(t_stack *a, t_stack *b, t_ops *ops)
{
	reverse_rotate(a);
	reverse_rotate(b);
	ops->rrr++;
	write(1, "rrr\n", 4);
}
