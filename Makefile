# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/06 18:09:59 by sdunckel          #+#    #+#              #
#    Updated: 2020/09/15 17:44:01 by sdunckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_containers

LIST			= list
STACK			= stack
QUEUE			= queue
VECTOR		= vector
MAP				= map
ALL				= $(LIST) $(STACK) $(QUEUE) $(VECTOR) $(MAP)

CC				= clang++
CFLAGS 		= -Wall -Wextra -Werror #-g -fsanitize=address
RM				= rm -f

all:			$(ALL)

$(LIST):	compile
					@${CC} ${CFLAGS} -o $@ tests/$@.cpp && ./$@

$(STACK):	compile
					@${CC} ${CFLAGS} -o $@ tests/$@.cpp && ./$@

$(QUEUE): compile
					@${CC} ${CFLAGS} -o $@ tests/$@.cpp && ./$@

$(VECTOR): compile
					@${CC} ${CFLAGS} -o $@ tests/$@.cpp && ./$@

$(MAP):		compile
					@${CC} ${CFLAGS} -o $@ tests/$@.cpp && ./$@

compile:

clean:
					${RM} $(ALL)

fclean:		clean

re:				fclean all

.PHONY: 	all fclean clean re