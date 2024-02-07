# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ricardo <ricardo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/28 17:48:30 by paula             #+#    #+#              #
#    Updated: 2024/02/07 18:04:27 by ricardo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =  ft_isalpha.c  ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c\
		ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c\
		ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c\
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c\
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c ft_printf_utils.c \
		./gnl/get_next_line.c ./gnl/get_next_line_utils.c

SRCS_B = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
		 ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

FLAGS = -Wall -Wextra -Werror

%.o: %.c
	@cc $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_B)
	@ar -crs $(NAME) $(OBJS) $(OBJS_B)

clean:
	@rm -f $(OBJS) $(OBJS_B)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re