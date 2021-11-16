NAME= minishell
FLAGS= -Werror -Wall -Wextra
SRCS= main.c check_token_syntax.c tools.c treat_pipe_sequence.c \
	 linked_list_tools.c vector.c char_vector.c freeing_functions.c \
	 dollar_var_handling.c treat_quotes.c expand_dollar_var.c \
	 split_dollar_var.c redirections.c export.c built_ins.c \
	 file_errors_handling.c exec_cmds.c built_ins_2.c check_cmds.c \
	 search_functions.c signals.c tools2.c split_dollar_var_2.c \
	 tokenize_cmd_line.c exec_cmds_2.c
OBJS= $(SRCS:.c=.o)
LIBFT= libft/libft.a

all: libft $(NAME)

libft:
	@make -C ./libft -j

$(NAME): $(LIBFT) $(OBJS)
	@gcc $(LIBFT) $(OBJS) -lreadline $(LDFLAGS) -o $(NAME)
	@echo
	@echo "---------- \033[1;36mSuccessfully generated minishell\033[0m ----------"
	@echo

%.o: %.c
	@echo Compiling : $< "\x1B[1;32m[OK]\x1B[0m"
	@gcc -g -c $< -o $@ $(CPPFLAGS)

clean:
	@make clean -C ./libft
	@rm -f *.o

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME)
	@echo
	@echo "---------- \033[1;36mSuccessfully deleted minishell\033[0m ----------"
	@echo

re: fclean all

.PHONY: libft