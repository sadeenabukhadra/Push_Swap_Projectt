/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:00:00 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/23 12:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	run_strategy(t_stack *a, t_stack *b, t_ops *ops, t_flags *flags)
{
	double	disorder;
	char	*strat;

	index_stack(a);
	disorder = compute_disorder(a);
	strat = "Complex / O(n log n)";
	if (flags->strategy == SIMPLE)
	{
		insertion_sort(a, b, ops);
		strat = "Simple / O(n^2)";
	}
	else if (flags->strategy == MEDIUM)
	{
		range_sort(a, b, ops);
		strat = "Medium / O(n*sqrt(n))";
	}
	else
		radix_sort(a, b, ops);
	if (flags->bench)
		print_bench(disorder, strat, ops);
}

static void	run_small(t_stack *a, t_stack *b, t_ops *ops, t_flags *flags)
{
	double	disorder;

	disorder = compute_disorder(a);
	if (a->size == 2)
	{
		if (a->top->value > a->top->next->value)
			sa(a, ops);
	}
	else if (a->size == 3)
		sort_three(a, ops);
	else
		sort_five(a, b, ops);
	if (flags->bench)
		print_bench(disorder, "Small / O(n)", ops);
}

static void	run_sort(t_stack *a, t_stack *b, t_ops *ops, t_flags *flags)
{
	if (a->size <= 5 && flags->strategy == ADAPTIVE)
	{
		run_small(a, b, ops, flags);
		return ;
	}
	if (flags->strategy == ADAPTIVE)
		adaptive_sort(a, b, ops, flags);
	else
		run_strategy(a, b, ops, flags);
}

static void	init_ops(t_ops *ops)
{
	ops->sa = 0;
	ops->sb = 0;
	ops->ss = 0;
	ops->pa = 0;
	ops->pb = 0;
	ops->ra = 0;
	ops->rb = 0;
	ops->rr = 0;
	ops->rra = 0;
	ops->rrb = 0;
	ops->rrr = 0;
}

int	main(int argc, char **argv)
{
	t_stack	a;
	t_stack	b;
	t_ops	ops;
	t_flags	flags;

	a.top = NULL;
	a.size = 0;
	b.top = NULL;
	b.size = 0;
	init_ops(&ops);
	parse_flags(argc, argv, &flags);
	parse_input(argc, argv, &a, &flags);
	if (!is_sorted(&a) && a.size > 1)
		run_sort(&a, &b, &ops, &flags);
	free_all_stacks(&a, &b);
	return (0);
}
