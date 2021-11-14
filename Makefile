NAME		=	minishell

CC			=	gcc

INC			=	-I./includes/ -I/Users/$(USER)/.brew/opt/readline/include

FLAGS		=	-Wall -Wextra -Werror #-g #-fsanitize=address

LIBFT_PATH	=	./libft

LIBFT		=	$(LIBFT_PATH)/libft.a

SRCS		=	./main.c ./signal.c ./execute.c ./tokenizer.c ./main_utils.c \
				./redirection.c ./list_reparsing.c\
				./split_list.c ./split_list_utils.c\
				./check_cmd.c ./env.c ./exit.c\
				./ft_strcmp.c ./echo.c ./pwd.c ./cd.c\
				./export.c ./unset.c ./ft_strjoin_ch.c\
				./cmdline.c ./split_list2.c ./sys_call.c ./redirection_utils.c\
				./error_print.c ./main_utils2.c ./reparse_rewind.c \
				./tokenizer2.c ./redirection_utils2.c ./execute2.c\
				./export_util.c ./builtin_util.c ./export_str.c\
				./cd_oldpwd.c ./cd_util.c ./change_dollar.c\
				./change_dollar2.c ./main_utils3.c\
				./tokenizer_util.c ./tokenizer_util2.c ./execute_utils.c\
				./echo_util.c ./cd_only.c

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

all			: 	$(NAME) ./minishell.h

$(NAME)		: $(OBJ) LIBFT
	@make bonus -C libft \
		&& make process

process		: ./minishell.h
	$(CC)  $(LIBS) $(FLAGS) $(HEADER_DIR) -o $(NAME) $(OBJ) $(LIBFT)

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
