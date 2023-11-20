.SILENT:

NAME		= 		minishell

SRCS		=		main.c

OBJS 		=		$(addprefix objs/, $(SRCS:.c=.o))

CFLAGS		=		-g -Wall -Wextra -Werror

RM			=		rm -f

COLOUR_GREEN=\033[32m
COLOUR_RED=\033[31m
COLOUR_END=\033[0m

objs/%.o: srcs/%.c
					@mkdir -p objs
					@cc $(CFLAGS) -c $< -o $@

${NAME}: ${OBJS}
	@echo "$(COLOUR_GREEN)----Compiling lib----"
	@make re -C ./libft
	@cc $(FLAGS) $(OBJS) -Llibft -lft -o $(NAME)
	@echo "$(COLOUR_GREEN)minishell Compiled! ᕦ$(COLOUR_RED)♥$(COLOUR_GREEN)_$(COLOUR_RED)♥$(COLOUR_GREEN)ᕤ\n$(COLOUR_END)"

all: ${NAME}

ifeq ($(shell uname), Linux)
install: install-linux
else
install: install-mac
endif

install-linux:
	@python3 -m pip install --upgrade pip setuptools
	@python3 -m pip install norminette
	@sudo apt update
	@sudo apt install valgrind -y

install-mac:
	@python3 -m pip install --upgrade pip setuptools
	@python3 -m pip install norminette

check:
	norminette
	norminette ./includes/minishell.h

clean:
	@make clean -C ./libft
	@rm -f ${OBJS}
	@echo "$(COLOUR_RED)Deleting all objs! ⌐(ಠ۾ಠ)¬\n$(COLOUR_END)"

fclean: clean
	@make fclean -C ./libft
	@rm -f ${NAME}
	@clear
	
re:			fclean all

.PHONY: all clean fclean re 