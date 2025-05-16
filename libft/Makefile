# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 15:33:02 by jdorazio          #+#    #+#              #
#    Updated: 2025/03/12 16:12:17 by jdorazio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

#  find *.c | xargs echo

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c\
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c\
	ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c\
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c\
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c\
	get_next_line.c get_next_line_utils.c ft_printf.c ft_utils.c

SRCS_BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c\
	ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

# varaible para transformar los .c en .o
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# variable de compilador
CC = cc

# variable de flags
CFLAGS = -Wall -Werror -Wextra

.c.o:
	${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}

# variable que da el enunciado
AR = ar rcs

# reglas
# all significa que al ejecturar make o make all, solo se hara las variables que esten dentro de la variable Name mas abajo
all: $(NAME)
# los archivos que hay que compilar primero SIN bonus
$(NAME): $(OBJS)
		$(AR) $(NAME) $(OBJS) -o $(NAME)
# los archivos que hay que compilar primero con bonus
bonus: $(OBJS) $(OBJS_BONUS) $(INCLUDE)
		$(AR) $(NAME) $(OBJS) $(OBJS_BONUS)

# borradores de archivos
clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean bonus

.PHONY: all clean fclean re
