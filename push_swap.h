/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 16:00:00 by sabu-kha          #+#    #+#             */
/*   Updated: 2026/03/19 17:00:00 by sabu-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include "libft/libft.h"

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	int		size;
}	t_stack;

typedef struct s_ops
{
	int	sa;
	int	sb;
	int	ss;
	int	pa;
	int	pb;
	int	ra;
	int	rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
}	t_ops;

typedef enum e_strategy
{
	SIMPLE,
	MEDIUM,
	COMPLEX,
	ADAPTIVE
}	t_strategy;

typedef struct s_flags
{
	int	bench;
	int	strategy;
}	t_flags;

void	swap(t_stack *stack);
void	sa(t_stack *a, t_ops *ops);
void	sb(t_stack *b, t_ops *ops);
void	ss(t_stack *a, t_stack *b, t_ops *ops);

void	push(t_stack *src, t_stack *dest);
void	pa(t_stack *a, t_stack *b, t_ops *ops);
void	pb(t_stack *a, t_stack *b, t_ops *ops);

void	rotate(t_stack *stack);
void	ra(t_stack *a, t_ops *ops);
void	rb(t_stack *b, t_ops *ops);
void	rr(t_stack *a, t_stack *b, t_ops *ops);

void	reverse_rotate(t_stack *stack);
void	rra(t_stack *a, t_ops *ops);
void	rrb(t_stack *b, t_ops *ops);
void	rrr(t_stack *a, t_stack *b, t_ops *ops);

void	init_stack(t_stack *a, int *numbers, int count);
void	free_all_stacks(t_stack *a, t_stack *b);

void	free_stack(t_stack *stack);
int		ft_isdigit(int c);
int		is_valid_number(char *str);
long	ft_atol(char *str);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
void	check_duplicates(int *arr, int size);
void	error_exit(void);

void	parse_input(int ac, char **argv, t_stack *a, t_flags *flags);
char	**split_args(char *arg);
void	parse_flags(int argc, char **argv, t_flags *flags);
void	parse_single_arg(char *arg, t_stack *a);
int		is_flag(char *s);
void	free_split(char **split);

int		is_sorted(t_stack *a);

void	sort_three(t_stack *a, t_ops *ops);
void	sort_five(t_stack *a, t_stack *b, t_ops *ops);

int		find_min_pos(t_stack *a);
void	push_min_to_b(t_stack *a, t_stack *b, t_ops *ops);
int		find_max_pos(t_stack *b);
void	move_max_to_top(t_stack *b, int pos, t_ops *ops);
int		find_insert_pos(t_stack *b, int index);

void	push_back(t_stack *a, t_stack *b, t_ops *ops);
void	insertion_sort(t_stack *a, t_stack *b, t_ops *ops);
void	radix_sort(t_stack *a, t_stack *b, t_ops *ops);
void	range_sort(t_stack *a, t_stack *b, t_ops *ops);

void	index_stack(t_stack *a);

double	compute_disorder(t_stack *a);
void	write_int(int fd, int n);
void	write_str(int fd, char *s);
void	print_disorder(double disorder);
void	print_bench(double disorder, char *strategy, t_ops *ops);
int		get_total_ops(t_ops *ops);
void	adaptive_sort(t_stack *a, t_stack *b, t_ops *ops, t_flags *flags);

#endif
