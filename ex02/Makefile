# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mriant <mriant@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 18:40:43 by mriant            #+#    #+#              #
#    Updated: 2023/05/10 19:02:14 by mriant           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = PmergeMe

SRCSDIR = srcs/
OBJSDIR = objs/

SRCS = ${addprefix ${SRCSDIR}, \
		 main.cpp \
		 .cpp}

OBJS = ${SRCS:${SRCSDIR}%.cpp=${OBJSDIR}%.o}
DEPS = ${SRCS:${SRCSDIR}%.cpp=${OBJSDIR}%.d}

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g
IFLAGS = -I./includes -MMD
LFLAGS =

${NAME}: ${OBJSDIR} ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJS} -o ${NAME} ${LFLAGS}

${OBJSDIR}:
	mkdir -p objs

${OBJSDIR}%.o: ${SRCSDIR}%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@ ${IFLAGS}

-include ${DEPS}

.PHONY: all
all: ${NAME}

.PHONY: clean
clean:
	rm -rf ${OBJSDIR}

.PHONY: fclean
fclean: clean
	rm -rf ${NAME}

.PHONY: re
re: fclean
	make -C .
