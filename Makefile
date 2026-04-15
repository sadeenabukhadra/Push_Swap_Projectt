# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabu-kha <sabu-kha@learner.42.tech>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/13 17:00:00 by sabu-kha          #+#    #+#              #
#    Updated: 2026/03/23 19:38:33 by sabu-kha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap
CC		= cc
CFLAGS		= -Wall -Wextra -Werror

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS		= main.c \
			  src/operations/swap_push.c \
			  src/operations/push.c \
			  src/operations/rotate.c \
			  src/operations/reverse.c \
			  src/sorting/sortcases.c \
			  src/sorting/sort_three.c \
			  src/sorting/sort_helpers.c \
			  src/sorting/insertion.c \
			  src/sorting/radix.c \
			  src/sorting/range.c \
			  src/sorting/adaptive.c \
			  src/sorting/bench.c \
			  src/sorting/bench2.c \
			  src/parsing/parse_flags.c \
			  src/parsing/parse_input.c \
			  src/parsing/parse_single.c \
			  src/parsing/split_args.c \
			  src/utils/init_stack.c \
			  src/utils/free_all.c \
			  src/utils/error_exit.c \
			  src/utils/check_duplicates.c \
			  src/utils/is_valid_number.c \
			  src/utils/ft_atol.c \
			  src/utils/ft_split.c \
			  src/utils/ft_isdigit.c \
			  src/utils/ft_strcmp.c

OBJS		= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -I. -I$(LIBFT_DIR) -c $< -o $@

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
