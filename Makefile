NAME= minishell
FLAGS= -Werror -Wall -Wextra
SRCS= tokenezation.c check_token_syntax.c
OBJS= $(SRCS:.c=.o)
LIBFT= libft/libft.a

all: libft $(NAME)

libft:
	@make -C ./libft -j

$(NAME): $(LIBFT) $(OBJS)
	@gcc $(LIBFT) $(OBJS) -lreadline -o $(NAME)
	@echo
	@echo "---------- \033[1;36mSuccessfully generated minishell\033[0m ----------"
	@echo

%.o: %.c
	@echo Compiling : $< "\x1B[1;32m[OK]\x1B[0m"
	@gcc -g -c $< -o $@

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