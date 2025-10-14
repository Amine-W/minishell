# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/12 11:54:28 by amwahab           #+#    #+#              #
#    Updated: 2025/10/14 18:42:03 by amwahab          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
TEST_NAME = test_lexer

CC = cc
CFLAGS = -Wall -Werror -Wextra

LEXER_SRCS = srcs/lexer/lexer.c \
			srcs/lexer/lexer_handlers.c \
			srcs/lexer/lexer_utils.c \
			 srcs/lexer/lexer_token.c

SRCS = srcs/main.c $(LEXER_SRCS)
TEST_SRCS = srcs/lexer/lexer_test.c $(LEXER_SRCS)

OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

test: $(TEST_NAME)

$(TEST_NAME) : $(TEST_OBJS) $(LIBFT)
	$(CC) $(TEST_OBJS) $(LIBFT) -lreadline -o $(TEST_NAME)


$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I includes -I $(LIBFT_DIR) -c $< -o $@
	
$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS) $(TEST_OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all test clean fclean re