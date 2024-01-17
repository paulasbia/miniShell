.SILENT:

NAME		= 		minishell
NAME_T		=		minishell_unit
LDLIBS		=		-lreadline -lft
MAIN		=		main.c
ENV			=		checks.c minishell.c mini_env.c
BUILTINS	=		pwd.c exit.c echo.c env.c utils.c unset.c export.c cd.c
UTILS		=		init_signal.c prompt.c frees.c error.c env_utils.c env_utils_2.c error2.c
EXECUTES	=		one_cmd.c exec_builtin.c exec_child.c
UNIT		=		main_teste.c unity.c
SRCS		=		$(MAIN) $(ENV) $(BUILTINS) $(UTILS) $(EXECUTES)
SRCS_T		=		$(ENV) $(BUILTINS) $(UTILS) $(EXECUTES) $(UNIT)

OBJS 		=		$(addprefix objs/, $(SRCS:.c=.o))
OBJS_T		=		$(addprefix objs/, $(SRCS_T:.c=.o))
CFLAGS		=		-g3 -Wall -Wextra -Werror

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
	norminette ./srcs
	norminette ./builtins
	norminette ./utils
	norminette ./executes
	norminette ./includes/minishell.h

pre_test:
	./e2e/tester.sh ./e2e/builtin
	./e2e/tester.sh ./e2e/extras

test:
	./e2e/tester.sh ./e2e/builtin
	./e2e/tester.sh ./e2e/extras
	./e2e/tester.sh ./e2e/redirects

${NAME_T}: ${OBJS_T}
	@echo "$(COLOUR_GREEN)----Compiling lib----"
	@make re -C ./libft
	@cc $(FLAGS) $(OBJS_T) -Llibft -lft -o $(NAME_T) $(LDLIBS)
	@echo "$(COLOUR_MAG)\nNice! Minishell Compiled! $(COLOUR_GREEN)ᕦ$(COLOUR_RED)♥$(COLOUR_GREEN)_$(COLOUR_RED)♥$(COLOUR_GREEN)ᕤ\n$(COLOUR_END)"
	@echo "$(COLOUR_MAG)\nTo start the program type ./minishell\nENJOY!\n$(COLOUR_END)"

unit: ${NAME_T}
	./${NAME_T}

clean:
	@make clean -C ./libft
	@rm -f ${OBJS} ${OBJS_T}
	@echo "$(COLOUR_RED)Deleting all objs! ⌐(ಠ۾ಠ)¬\n$(COLOUR_END)"

fclean: clean
	@make fclean -C ./libft
	@rm -f ${NAME}
	@clear
	
re:			fclean all

.PHONY: all clean fclean re 