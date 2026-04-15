/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:48:41 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 17:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

/*
** All 6 permutations of (first, second, third) -> operation(s):
**   1 2 3  sorted          -> nothing
**   2 1 3  max in middle   -> sa
**   3 2 1  descending      -> sa rra
**   3 1 2  max on top      -> ra
**   1 3 2  max in middle   -> sa ra
**   2 3 1  min on top      -> rra
**
** Each condition is an exact match of exactly one permutation shape,
** expressed as direct value comparisons — no arithmetic on values,
** which broke with negatives in the old helper approach.
*/
void	sort_three(t_stack *a, t_ops *ops)
{
	int	f;
	int	s;
	int	t;

	if (a->size < 2 || is_sorted(a))
		return ;
	f = a->top->value;
	s = a->top->next->value;
	t = a->top->next->next->value;
	if (f > s && s < t && f < t)
		sa(a, ops);
	else if (f > s && s > t)
	{
		sa(a, ops);
		rra(a, ops);
	}
	else if (f > s && s < t && f > t)
		ra(a, ops);
	else if (f < s && s > t && f < t)
	{
		sa(a, ops);
		ra(a, ops);
	}
	else if (f < s && s > t && f > t)
		rra(a, ops);
}
