# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/06 19:50:41 by hchadili          #+#    #+#              #
#    Updated: 2024/11/14 20:51:14 by hchadili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC =	main.c 				\
		ft_atoi.c			\
		pars.c				\
		set_value.c			\
		routing.c			\
		monitor.c			\
		set_up_philos.c		\

OBJS = $(SRC:.c=.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) -pthread $(OBJS) -o $(NAME)

%.o : %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
fclean:	clean
	$(RM) $(NAME)

re: fclean all
