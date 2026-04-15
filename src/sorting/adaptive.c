/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:19:00 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 18:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

void	index_stack(t_stack *a)
{
	t_node	*i;
	t_node	*j;
	int		rank;

	i = a->top;
	while (i)
	{
		rank = 0;
		j = a->top;
		while (j)
		{
			if (j->value < i->value)
				rank++;
			j = j->next;
		}
		i->index = rank;
		i = i->next;
	}
}

static char	*pick_algorithm(t_stack *a, t_stack *b, t_ops *ops, double dis)
{
	if (dis < 0.2)
	{
		insertion_sort(a, b, ops);
		return ("Adaptive / O(n^2)");
	}
	else if (dis < 0.5)
	{
		radix_sort(a, b, ops);
		return ("Adaptive / O(n*sqrt(n))");
	}
	else
	{
		radix_sort(a, b, ops);
		return ("Adaptive / O(n log n)");
	}
}

void	adaptive_sort(t_stack *a, t_stack *b, t_ops *ops, t_flags *flags)
{
	double	disorder;
	char	*strategy;

	if (is_sorted(a))
		return ;
	index_stack(a);
	disorder = compute_disorder(a);
	strategy = pick_algorithm(a, b, ops, disorder);
	if (flags->bench)
		print_bench(disorder, strategy, ops);
}
