# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/06 18:09:59 by sdunckel          #+#    #+#              #
#    Updated: 2021/03/29 16:10:35 by sdunckel         ###   ########.fr        #
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
CFLAGS 		= -Wall -Wextra -Werror -std=c++98
LFLAGS		= #-I .
FSANI			= #-g -fsanitize=address
RM				= rm -f

all:			$(ALL)

$(LIST):	compile
					@${CC} ${CFLAGS} $(LFLAGS) ${FSANI} -o $@ tests/test_$@.cpp && ./$@

$(STACK):	compile
					@${CC} ${CFLAGS} $(LFLAGS) ${FSANI} -o $@ tests/test_$@.cpp && ./$@

$(QUEUE):	compile
					@${CC} ${CFLAGS} $(LFLAGS) ${FSANI} -o $@ tests/test_$@.cpp && ./$@

$(VECTOR): compile
					@${CC} ${CFLAGS} $(LFLAGS) ${FSANI} -o $@ tests/test_$@.cpp && ./$@

$(MAP):		compile
					@${CC} ${CFLAGS} $(LFLAGS) ${FSANI} -o $@ tests/test_$@.cpp && ./$@

compile:

clean:
					${RM} $(ALL)

fclean:		clean

re:				fclean all

.PHONY: 	all fclean clean re