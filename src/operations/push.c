/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:00:00 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 17:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

void	pa(t_stack *a, t_stack *b, t_ops *ops)
{
	push(b, a);
	ops->pa++;
	write(1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b, t_ops *ops)
{
	push(a, b);
	ops->pb++;
	write(1, "pb\n", 3);
}
