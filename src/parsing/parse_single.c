/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 19:33:44 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 17:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

static int	count_words(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static int	*args_to_numbers(char **args, int count)
{
	int		*numbers;
	long	num;
	int		i;

	numbers = malloc(sizeof(int) * count);
	if (!numbers)
		error_exit();
	i = 0;
	while (i < count)
	{
		if (!is_valid_number(args[i]))
			error_exit();
		num = ft_atol(args[i]);
		if (num > 2147483647 || num < -2147483648)
			error_exit();
		numbers[i] = (int)num;
		i++;
	}
	return (numbers);
}

void	parse_single_arg(char *arg, t_stack *a)
{
	char	**args;
	int		*numbers;
	int		count;

	args = split_args(arg);
	count = count_words(args);
	numbers = args_to_numbers(args, count);
	check_duplicates(numbers, count);
	init_stack(a, numbers, count);
	free(numbers);
	free_split(args);
}
