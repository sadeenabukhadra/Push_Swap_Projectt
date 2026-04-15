/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 14:25:42 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 18:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

static int	get_range(int size)
{
	int	range;

	range = 0;
	while ((range + 1) * (range + 1) <= size)
		range++;
	return (range);
}

static void	push_chunk_element(t_stack *a, t_stack *b, t_ops *ops, int *ctx)
{
	if (a->top->index <= ctx[0])
	{
		pb(a, b, ops);
		if (a->top && a->top->index <= ctx[0] + ctx[2])
			ctx[0] = ctx[0];
		ctx[1] = 0;
	}
	else if (a->top->index <= ctx[0] + ctx[2])
	{
		pb(a, b, ops);
		ctx[1] = 0;
	}
	else
	{
		ra(a, ops);
		ctx[1]++;
		if (ctx[1] >= a->size)
		{
			ctx[0] += ctx[2];
			ctx[1] = 0;
		}
	}
}

static void	push_chunks(t_stack *a, t_stack *b, int range, t_ops *ops)
{
	int	ctx[3];

	ctx[0] = range - 1;
	ctx[1] = 0;
	ctx[2] = range;
	while (a->size > 0)
		push_chunk_element(a, b, ops, ctx);
}

static void	push_backk(t_stack *b, t_stack *a, t_ops *ops)
{
	int	pos;

	while (b->size > 0)
	{
		pos = find_max_pos(b);
		move_max_to_top(b, pos, ops);
		pa(a, b, ops);
	}
}

void	range_sort(t_stack *a, t_stack *b, t_ops *ops)
{
	int	range;

	if (is_sorted(a))
		return ;
	range = get_range(a->size);
	push_chunks(a, b, range, ops);
	push_backk(b, a, ops);
}
