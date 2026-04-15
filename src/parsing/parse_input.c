/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 19:33:44 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 17:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

int	is_flag(char *s)
{
	return (s[0] == '-' && s[1] == '-');
}

static int	count_nums(int argc, char **argv)
{
	int	count;
	int	i;

	count = 0;
	i = 1;
	while (i < argc)
	{
		if (!is_flag(argv[i]))
			count++;
		i++;
	}
	return (count);
}

static int	*convert_nums(int argc, char **argv, int count)
{
	int		*numbers;
	long	num;
	int		i;
	int		j;

	numbers = malloc(sizeof(int) * count);
	if (!numbers)
		error_exit();
	j = 0;
	i = 1;
	while (i < argc)
	{
		if (!is_flag(argv[i]))
		{
			if (!is_valid_number(argv[i]))
				error_exit();
			num = ft_atol(argv[i]);
			if (num > 2147483647 || num < -2147483648)
				error_exit();
			numbers[j++] = (int)num;
		}
		i++;
	}
	check_duplicates(numbers, count);
	return (numbers);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	parse_input(int ac, char **argv, t_stack *a, t_flags *flags)
{
	int		count;
	int		*numbers;

	(void)flags;
	if (ac < 2)
		exit(0);
	if (ac == 2 && !is_flag(argv[1]))
	{
		parse_single_arg(argv[1], a);
		return ;
	}
	count = count_nums(ac, argv);
	if (count == 0)
		exit(0);
	numbers = convert_nums(ac, argv, count);
	init_stack(a, numbers, count);
	free(numbers);
}
