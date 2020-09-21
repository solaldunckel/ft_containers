# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/06 18:09:59 by sdunckel          #+#    #+#              #
#    Updated: 2020/09/16 17:38:47 by sdunckel         ###   ########.fr        #
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
CFLAGS 		= -Wall -Wextra -Werror
FSANI			= -g -fsanitize=address
RM				= rm -f

all:			$(ALL)

$(LIST):
					@${CC} ${CFLAGS} ${FSANI} -o $@ tests/test_$@.cpp && ./$@

$(STACK):
					@${CC} ${CFLAGS} ${FSANI} -o $@ tests/test_$@.cpp && ./$@

$(QUEUE):
					@${CC} ${CFLAGS} ${FSANI} -o $@ tests/test_$@.cpp && ./$@

$(VECTOR): compile
					@${CC} ${CFLAGS} ${FSANI} -o $@ tests/test_$@.cpp && ./$@

$(MAP):		compile
					@${CC} ${CFLAGS} ${FSANI} -o $@ tests/test_$@.cpp && ./$@

compile:

clean:
					${RM} $(ALL)

fclean:		clean

re:				fclean all

.PHONY: 	all fclean clean re