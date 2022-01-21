# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kamori <velvelhype@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 03:20:19 by kamori            #+#    #+#              #
#    Updated: 2022/01/21 13:52:15 by kamori           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Werror -Wall -Wextra
#CFLAGS = -Werror -Wall -Wextra -g -fsanitize=thread
# CFLAGS = -Werror -Wall -Wextra -g -fsanitize=address
SRCS = main.c \
philo_life.c \
utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
