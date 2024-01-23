.SILENT:

NAME		= 		minishell
LDLIBS		=		-lreadline -lft
MAIN		=		main.c checks.c minishell.c
BUILTINS	=		pwd.c exit.c echo.c env.c utils.c unset.c export.c
UTILS		=		init_signal.c prompt.c frees.c error.c
EXECUTES	=		one_cmd.c
PARSING		=		parsing.c split_pipe.c split_minishell.c validate_input.c clean_quotes.c
SRCS		=		$(MAIN) $(BUILTINS) $(UTILS) $(EXECUTES) $(PARSING)

OBJS 		=		$(addprefix objs/, $(SRCS:.c=.o))

CFLAGS		=	    -g -Wall -Wextra -Werror

RM			=		rm -f

COLOUR_GREEN=\033[32m
COLOUR_RED=\033[31m
COLOUR_END=\033[0m
COLOUR_MAG=\001\e[0;35m\002

objs/%.o: */%.c
					@mkdir -p objs
					@cc $(CFLAGS) -c $< -o $@

${NAME}: ${OBJS}
	@echo "$(COLOUR_GREEN)----Compiling lib----"
	@make re -C ./libft
	@cc $(FLAGS) $(OBJS) -Llibft -lft -o $(NAME) $(LDLIBS)
	@echo "$(COLOUR_MAG)\nNice! Minishell Compiled! $(COLOUR_GREEN)ᕦ$(COLOUR_RED)♥$(COLOUR_GREEN)_$(COLOUR_RED)♥$(COLOUR_GREEN)ᕤ\n$(COLOUR_END)"
	@echo "$(COLOUR_MAG)\nTo start the program type ./minishell\nENJOY!\n$(COLOUR_END)"

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