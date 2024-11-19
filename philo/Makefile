# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 03:45:04 by hchadili          #+#    #+#              #
#    Updated: 2024/11/07 19:49:11 by hchadili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
SRC =	main.c 				\
		ft_atoi.c			\
		monitor.c			\
		routing.c			\
		routing_philo.c		\
		pars.c				\
		set_value.c			\
		
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
