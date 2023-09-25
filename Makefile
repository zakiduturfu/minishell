NAME = minishell

FOLDER = ./

SRCS = ./src/main.c \
	./src/parsing/pars_cmd_line.c \
	./src/parsing/token.c \
	./src/parsing/split_token.c \
	./src/file/redirections.c \
	./src/pipex/pipex.c \
	./src/pipex/here_doc.c \
	./src/pipex/process.c \
	./src/env/env.c \
	./src/env/shlvl.c \
	./src/env/expansions.c \
	./src/tools/parsing/token_utils.c \
	./src/tools/parsing/pars_cmd_line_utils.c \
	./src/tools/env/env_utils.c \
	./src/tools/env/expansions_utils.c \
	./src/tools/file/redirections_utils.c \
	./src/tools/file/free_close.c \
	./src/builtins/exec.c \
	./src/builtins/echo.c \
	./src/builtins/export.c \
	./src/builtins/unset.c \
	./src/builtins/utils.c \
	./src/builtins/cd.c \

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