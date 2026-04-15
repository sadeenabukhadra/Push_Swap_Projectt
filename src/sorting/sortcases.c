/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortcases.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:48:41 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 18:30:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

int	is_sorted(t_stack *a)
{
	t_node	*tmp;

	tmp = a->top;
	while (tmp && tmp->next)
	{
		if (tmp->value > tmp->next->value)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

/*
** sort_five handles sizes 3, 4, and 5.
**
** FIX: The original pushed 2 elements then called sort_three regardless
** of the starting size.  For size=4 that leaves only 2 elements in a
** after 2 pushes, so sort_three tried to access a->top->next->next = NULL.
**
** Correct logic:
**   size=3 -> just sort_three directly
**   size=4 -> push 1 minimum, sort_three on the remaining 3, pa once
**   size=5 -> push 2 minimums, sort_three on the remaining 3, pa twice
*/
void	sort_five(t_stack *a, t_stack *b, t_ops *ops)
{
	if (is_sorted(a))
		return ;
	if (a->size == 3)
	{
		sort_three(a, ops);
		return ;
	}
	if (a->size == 4)
	{
		push_min_to_b(a, b, ops);
		sort_three(a, ops);
		pa(a, b, ops);
		return ;
	}
	push_min_to_b(a, b, ops);
	push_min_to_b(a, b, ops);
	sort_three(a, ops);
	pa(a, b, ops);
	pa(a, b, ops);
}
