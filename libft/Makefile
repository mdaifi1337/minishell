NAME= libft.a
SRCS= ft_atoi.c ft_bzero.c ft_isalnum.c ft_isascii.c ft_isalpha.c ft_calloc.c ft_isprint.c \
		ft_isdigit.c ft_memchr.c ft_memcmp.c ft_memccpy.c ft_memset.c ft_memmove.c ft_memcpy.c \
		ft_itoa.c ft_putendl_fd.c ft_putnbr_fd.c ft_strlen.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_strchr.c ft_strdup.c ft_strlcpy.c ft_strlcat.c ft_strjoin.c ft_strmapi.c ft_strrchr.c \
		ft_strnstr.c ft_split.c ft_toupper.c ft_strncmp.c ft_tolower.c ft_substr.c ft_strtrim.c \
		ft_bzero.c ft_memmove.c ft_strjoin.c ft_lstnew.c ft_lstadd_front.c ft_lstadd_back.c \
		ft_lstclear.c ft_lstdelone.c ft_lstsize.c ft_lstlast.c ft_lstiter.c ft_lstmap.c \
		ft_free_array.c ft_strcmp.c
OBJ=$(SRCS:.c=.o)
BOBJ=$(BONUSES:.c=.o)
FLG= -c -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "---------- \033[1;36mSuccessfully created libft.a\033[0m ----------"
	@echo
%.o: %.c
	@echo Compiling : $< "\x1B[1;32m[OK]\x1B[0m"
	@gcc $(FLG) $<

clean:
	@/bin/rm -f *.o

fclean: clean
	@/bin/rm -f $(NAME)
	@echo
	@echo "---------- \033[1;36mSuccessfully deleted libft.a\033[0m   ----------"
