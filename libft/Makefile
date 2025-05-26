# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 15:33:02 by jdorazio          #+#    #+#              #
#    Updated: 2025/05/26 19:44:11 by mamaratr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

DEF_COLOR = \033[0;39m
BRIGHT_GREEN = \033[1;92m

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c\
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c\
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c\
	get_next_line.c get_next_line_utils.c ft_printf.c ft_utils.c

SRCS_BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c\
	ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c\
	ft_lstnew_bonus.c ft_lstsize_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
DEPS = $(OBJS:.o=.d) $(OBJS_BONUS:.o=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -g -fPIC
AR = ar rcs
RM = rm -f

.c.o:
	@$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

-include $(DEPS)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(BRIGHT_GREEN)Created ${NAME} ✓$(DEF_COLOR)"

bonus: $(OBJS) $(OBJS_BONUS)
	@$(AR) $(NAME) $(OBJS) $(OBJS_BONUS)

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS) $(DEPS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re