/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:19:33 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 18:30:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

double	compute_disorder(t_stack *a)
{
	t_node	*i;
	t_node	*j;
	int		mistakes;
	int		total_pairs;

	i = a->top;
	mistakes = 0;
	total_pairs = 0;
	while (i)
	{
		j = i->next;
		while (j)
		{
			total_pairs++;
			if (i->value > j->value)
				mistakes++;
			j = j->next;
		}
		i = i->next;
	}
	if (total_pairs == 0)
		return (0);
	return ((double)mistakes / total_pairs);
}

int	get_total_ops(t_ops *ops)
{
	return (ops->sa + ops->sb + ops->ss
		+ ops->pa + ops->pb
		+ ops->ra + ops->rb + ops->rr
		+ ops->rra + ops->rrb + ops->rrr);
}

void	write_int(int fd, int n)
{
	ft_putnbr_fd(n, fd);
}

void	write_str(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
}

void	print_disorder(double disorder)
{
	int	whole;
	int	decimals;

	whole = (int)(disorder * 100);
	decimals = (int)(disorder * 10000) % 100;
	write_str(2, "[bench] disorder: ");
	write_int(2, whole);
	write_str(2, ".");
	if (decimals < 10)
		write_str(2, "0");
	write_int(2, decimals);
	write_str(2, "%\n");
}
