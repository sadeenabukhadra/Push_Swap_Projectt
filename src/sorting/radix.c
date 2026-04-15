/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 15:30:35 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 17:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

static void	process_bit(t_stack *a, t_stack *b, t_ops *ops, int bit)
{
	int	j;
	int	size;

	size = a->size;
	j = 0;
	while (j++ < size)
	{
		if (((a->top->index >> bit) & 1) == 1)
			ra(a, ops);
		else
			pb(a, b, ops);
	}
}

void	radix_sort(t_stack *a, t_stack *b, t_ops *ops)
{
	int	i;
	int	max_bits;
	int	size;

	size = a->size;
	max_bits = 0;
	while ((size >> max_bits) != 0)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		process_bit(a, b, ops, i);
		push_back(a, b, ops);
		i++;
	}
}
