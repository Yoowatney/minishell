NAME		=	minishell

CC			=	gcc

INC			=	-I./includes/ -I/Users/$(USER)/.brew/opt/readline/include

FLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address

LIBFT_PATH	=	./libft

LIBFT		=	$(LIBFT_PATH)/libft.a

SRCS		=	./main.c ./signal.c ./execute.c ./tokenizer.c ./utils.c

OBJ			=	$(SRCS:.c=.o)


ifdef LOCAL
	LIBS		=	-lreadline   -L/usr/local/opt/readline/lib
	HEADER_DIR	=	-I./includes -I/usr/local/opt/readline/include
else ifdef M1
	LIBS		=	-lreadline -L/opt/homebrew/opt/readline/lib
	HEADER_DIR	=	-I./includes -I/opt/homebrew/opt/readline/include
else
	LIBS		=	-lreadline -L/Users/$(USER)/.brew/opt/readline/lib
	HEADER_DIR	=	-I./includes -I/Users/$(USER)/.brew/opt/readline/include
endif

all			: 	$(NAME)

$(NAME)		: $(OBJ) LIBFT
	@echo "libft compiling" \
		&& echo "... loading ..."
	@make bonus -C libft
	@echo "libft succesfully compiled."
	@echo "minishell compiling" \
		&& make process

process		: ./minishell.h
	$(CC)  $(LIBS) $(FLAGS) $(HEADER_DIR) -o $(NAME) $(OBJ) $(LIBFT)
	echo "minishell succesfully compiled."

%.o			: %.c
	$(CC) $(FLAGS) $(HEADER_DIR) -o $@ -c $<

clean		:
	make -C $(LIBFT_PATH) $@
	rm -f $(OBJ)

fclean		: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re			:
	@make clean
	@make all

.PHONY		: all clean fclean re process