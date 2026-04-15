/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 15:15:11 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 17:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../push_swap.h"

void	parse_flags(int argc, char **argv, t_flags *flags)
{
	int	i;

	flags->bench = 0;
	flags->strategy = ADAPTIVE;
	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--bench") == 0)
			flags->bench = 1;
		else if (ft_strcmp(argv[i], "--simple") == 0)
			flags->strategy = SIMPLE;
		else if (ft_strcmp(argv[i], "--medium") == 0)
			flags->strategy = MEDIUM;
		else if (ft_strcmp(argv[i], "--complex") == 0)
			flags->strategy = COMPLEX;
		else if (ft_strcmp(argv[i], "--adaptive") == 0)
			flags->strategy = ADAPTIVE;
		i++;
	}
}
