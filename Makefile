# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdunckel <sdunckel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/06 18:09:59 by sdunckel          #+#    #+#              #
#    Updated: 2020/09/02 11:26:56 by sdunckel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_containers

LIST			= list
STACK			= stack
QUEUE			= queue
VECTOR		= vector
MAP				= map

CC				= clang++
CFLAGS 		= -Wall -Wextra -Werror
RM				= rm -f

all:			$(LIST) $(STACK)

$(LIST):	compile
					@${CC} ${CFLAGS} -o $@ tests/$@.cpp && ./$@

$(STACK):	compile
					@${CC} ${CFLAGS} -o $@ tests/$@.cpp && ./$@

$(VECTOR):	compile
					@${CC} ${CFLAGS} -o $@ tests/$@.cpp && ./$@

compile:

clean:
					${RM} $(LIST) $(VECTOR) $(STACK)

fclean:		clean

re:				fclean all

.PHONY: 	all fclean clean re