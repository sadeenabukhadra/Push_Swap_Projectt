/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:19:33 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 18:30:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

static void	print_ops_line1(t_ops *ops)
{
	write_str(2, "[bench] sa: ");
	write_int(2, ops->sa);
	write_str(2, " sb: ");
	write_int(2, ops->sb);
	write_str(2, " ss: ");
	write_int(2, ops->ss);
	write_str(2, " pa: ");
	write_int(2, ops->pa);
	write_str(2, " pb: ");
	write_int(2, ops->pb);
	write_str(2, "\n");
}

static void	print_ops_line2(t_ops *ops)
{
	write_str(2, "[bench] ra: ");
	write_int(2, ops->ra);
	write_str(2, " rb: ");
	write_int(2, ops->rb);
	write_str(2, " rr: ");
	write_int(2, ops->rr);
	write_str(2, " rra: ");
	write_int(2, ops->rra);
	write_str(2, " rrb: ");
	write_int(2, ops->rrb);
	write_str(2, " rrr: ");
	write_int(2, ops->rrr);
	write_str(2, "\n");
}

void	print_bench(double disorder, char *strategy, t_ops *ops)
{
	print_disorder(disorder);
	write_str(2, "[bench] strategy: ");
	write_str(2, strategy);
	write_str(2, "\n");
	write_str(2, "[bench] total_ops: ");
	write_int(2, get_total_ops(ops));
	write_str(2, "\n");
	print_ops_line1(ops);
	print_ops_line2(ops);
}
