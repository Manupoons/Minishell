NAME = minishell

DEF_COLOR = \033[0;39m
BRIGHT_GREEN =	\033[1;92m

SRC = src/main.c src/commands.c

LIBFT = libft/libft.a

INC = ./inc/minishell.h

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -MMD -I./inc -g -Ilibft
LDFLAGS = -lreadline

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

OBJS = ${SRC:.c=.o}
DEPS = $(addsuffix .d, $(basename $(SRC)))

all: ${NAME}

-include $(DEPS)
${NAME}: ${OBJS}
	@${CC} ${OBJS} -o $(NAME) $(LDFLAGS)
	@echo "\n$(BRIGHT_GREEN)Created ${NAME} ✓$(DEF_COLOR)\n"

clean:
	@${RM} ${OBJS} ${DEPS}
	@echo "\n$(BRIGHT_GREEN)All objects cleaned successfully ✓$(DEF_COLOR)\n"

fclean:
	@${RM} ${OBJS} ${DEPS} ${NAME}
	@echo "\n$(BRIGHT_GREEN)All objects and executable cleaned successfully ✓$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re