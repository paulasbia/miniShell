.SILENT:

NAME		= 		minishell
NAME_T		=		minishell_unit
LDLIBS		=		-lreadline -lft
PARSING		=		parsing.c split_pipe.c split_minishell.c validate_input.c clean_quotes.c count_split_ms.c free_parsing.c
MAIN		=		main.c
ENV			=		checks.c minishell.c mini_env.c
BUILTINS	=		pwd.c exit.c echo.c env.c utils.c unset.c export.c cd.c
UTILS		=		init_signal.c prompt.c frees.c error.c env_utils.c env_utils_2.c error2.c exec_utils.c
EXECUTES	=		one_cmd.c exec_builtin.c exec_child.c redirects.c exec_mult.c wait.c heredoc.c
UNIT		=		main_teste.c unity.c
SRCS		=		$(MAIN) $(ENV) $(BUILTINS) $(UTILS) $(EXECUTES) $(PARSING)
SRCS_T		=		$(ENV) $(BUILTINS) $(UTILS) $(EXECUTES) $(UNIT) $(PARSING)

OBJS 		=		$(addprefix objs/, $(SRCS:.c=.o))
OBJS_T		=		$(addprefix objs/, $(SRCS_T:.c=.o))
CFLAGS		=		-g3 -Wall -Wextra

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
	@echo "  $(COLOUR_MAG)                                                                        ";
	@echo "💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟";
	@echo "                           _    _                   _          _                       ";
	@echo "                          |  \/  (_)_ __ (_)___ ___| |__   ___| |                       ";
	@echo "                          | |\/| | | '_ \| / __/ __| '_ \ / _ \ |                       ";
	@echo "                          | |  | | | | | | \__ \__ \ | | |  __/ |                       ";
	@echo "                          |_|  |_|_|_| |_|_|___/___/_| |_|\___|_|                       ";
	@echo "                                                                   By pde-souz          ";
	@echo "                                                                      tbolzan-          ";
	@echo "💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟💟";
	@echo "                                                                                         ";

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
	norminette ./parsing
	norminette ./includes/minishell.h

test_u:
	./e2e/tester.sh ./e2e/os_specifics

test:
	./e2e/tester.sh ./e2e/builtin
	./e2e/tester.sh ./e2e/extras
	./e2e/tester.sh ./e2e/redirects
	./e2e/tester.sh ./e2e/pipes
	./e2e/tester.sh ./e2e/sintaxe
	./e2e/tester.sh ./e2e/os_specifics

valgrind:
	valgrind --leak-check=full ./minishell

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