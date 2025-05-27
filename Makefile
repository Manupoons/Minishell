NAME = minishell

DEF_COLOR = \033[0;39m
BRIGHT_GREEN = \033[1;92m

SRC_DIR = src
SRC = $(shell find $(SRC_DIR) -name "*.c")
OBJS = ${SRC:.c=.o}
DEPS = $(OBJS:.o=.d)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

INC = ./inc/minishell.h

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -MMD -I./inc -g -I$(LIBFT_DIR)
LDFLAGS = -lreadline

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "Building libft..."
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

-include $(DEPS)

$(NAME): $(OBJS) $(LIBFT)
	@${CC} ${OBJS} ${LIBFT} -o ${NAME} $(LDFLAGS)
	@echo "\n$(BRIGHT_GREEN)Created ${NAME} ✓$(DEF_COLOR)\n"

clean:
	@${RM} ${OBJS} ${DEPS}
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "\n$(BRIGHT_GREEN)All objects cleaned successfully ✓$(DEF_COLOR)\n"

fclean: clean
	@${RM} ${NAME}
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "\n$(BRIGHT_GREEN)All objects and executable cleaned successfully ✓$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re
