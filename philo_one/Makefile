# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rofernan <rofernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/14 15:53:42 by rofernan          #+#    #+#              #
#    Updated: 2020/09/14 15:53:44 by rofernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_one

SRCS		=	actions.c \
				display.c \
				exit.c \
				init.c \
				main.c \
				time.c \
				utils.c

INC			=	philosophers.h

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -I./

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

clean:
				rm -rf $(OBJS)

fclean:
				rm -rf $(OBJS) $(NAME)

re:				fclean all

.PHONY:			clean fclean re all
