NAME = minishell

FOLDER = ./

SRCS = ./src/main.c

HEADER = include

SRCS_ALL = ${addprefix ${FOLDER}, ${SRCS}}

OBJS = ${SRCS_ALL:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

all: ${NAME}

.c.o:
	${CC} ${CLFAGS} -I${HEADER} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -I${HEADER} -o $@ $^

clean:
	rm -f ${OBJS}

fclean:	clean
		rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re