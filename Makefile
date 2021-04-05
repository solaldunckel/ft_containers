# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/06 18:09:59 by sdunckel          #+#    #+#              #
#    Updated: 2021/04/05 17:28:19 by sdunckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_containers_test

CC				= clang++
CFLAGS 		= -Wall -Wextra -Werror -std=c++98
LFLAGS		= -I includes/ -I tests/
RM				= rm -f

OBJS			= $(SRCS:.cpp=.o)

SRCS			= tests/vector.cpp \
						tests/map.cpp \
						tests/list.cpp \
						tests/stack.cpp \
						tests/queue.cpp \
						main.cpp

all:			$(NAME)

$(NAME):	$(OBJS)
					${CC} ${CFLAGS} $(LFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
					${CC} $(LFLAGS) -o $@ -c $<

clean:
					${RM} $(OBJS)

fclean:		clean
					${RM} $(NAME)

re:				fclean all

.PHONY: 	all fclean clean re