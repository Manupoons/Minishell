# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 15:33:02 by jdorazio          #+#    #+#              #
#    Updated: 2025/05/28 17:54:16 by mamaratr         ###   ########.fr        #
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
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_memfree.c\
	ft_memfree_all.c ft_strcmp.c ft_array.c

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