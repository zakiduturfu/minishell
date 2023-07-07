NAME = minishell

FOLDER = ./

SRCS = ./src/main.c \
	./src/parsing/pars_cmd_line.c \
	./src/parsing/token.c \
	./src/parsing/token_utils.c

HEADER = include

SRCS_ALL = ${addprefix ${FOLDER}, ${SRCS}}
LIBFT = libft 
LIB_PATH = libft/libft.a

OBJS = ${SRCS_ALL:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra -g
CLINK = -lreadline

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -I${LIBFT} -I${HEADER} -c $< -o $@

${NAME}: ${OBJS} ${LIB_PATH}
	${CC} ${CFLAGS} -I${HEADER} -I${LIBFT} -L${LIBFT} -o $@ $^ ${CLINK}

${LIB_PATH}:
	cd ${LIBFT} && make

clean:
	rm -f ${OBJS}
	cd ${LIBFT} && make clean

fclean:	clean
		rm -f ${NAME}
		cd ${LIBFT} && make fclean


re: fclean all

.PHONY: all clean fclean re