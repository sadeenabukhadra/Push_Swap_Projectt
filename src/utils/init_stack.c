/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 19:36:48 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 17:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

static t_node	*new_node(int value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = value;
	node->index = 0;
	node->next = NULL;
	return (node);
}

static void	add_node_back(t_stack *stack, t_node *new)
{
	t_node	*tmp;

	if (!stack->top)
		stack->top = new;
	else
	{
		tmp = stack->top;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	stack->size++;
}

void	init_stack(t_stack *a, int *numbers, int count)
{
	int		i;
	t_node	*node;

	a->top = NULL;
	a->size = 0;
	i = 0;
	while (i < count)
	{
		node = new_node(numbers[i]);
		if (!node)
			error_exit();
		add_node_back(a, node);
		i++;
	}
}
