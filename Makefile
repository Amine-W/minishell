# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/12 11:54:28 by amwahab           #+#    #+#              #
#    Updated: 2025/10/20 15:45:51 by amwahab          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
TEST_LEXER = test_lexer
TEST_AST = test_ast
TEST_PARSER = test_parser

CC = cc
CFLAGS = -Wall -Werror -Wextra

LEXER_SRCS = srcs/lexer/lexer.c \
			srcs/lexer/lexer_handlers.c \
			srcs/lexer/lexer_utils.c \
			srcs/lexer/lexer_token.c

AST_SRCS = srcs/ast/ast_node.c \
			srcs/ast/ast_utils.c 

PARSER_SRCS = srcs/parser/parser.c \
			srcs/parser/parser_utils.c \
			srcs/parser/parser_command.c \
			srcs/parser/parser_command_utils.c

SRCS = srcs/main.c $(LEXER_SRCS)
TEST_LEXER_SRCS = srcs/lexer/lexer_test.c $(LEXER_SRCS)
TEST_AST_SRCS = srcs/ast/ast_test.c $(AST_SRCS)
TEST_PARSER_SRCS = srcs/parser/parser_test.c $(LEXER_SRCS) $(AST_SRCS) $(PARSER_SRCS)


OBJS = $(SRCS:.c=.o)
TEST_LEXER_OBJS = $(TEST_LEXER_SRCS:.c=.o)
TEST_AST_OBJS = $(TEST_AST_SRCS:.c=.o)
TEST_PARSER_OBJS = $(TEST_PARSER_SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

test_ast: $(TEST_AST)


$(TEST_PARSER): $(TEST_PARSER_OBJS) $(LIBFT)
	$(CC) $(TEST_PARSER_OBJS) $(LIBFT) -lreadline -o $(TEST_PARSER)

$(TEST_LEXER): $(TEST_LEXER_OBJS) $(LIBFT)
	$(CC) $(TEST_LEXER_OBJS) $(LIBFT) -lreadline -o $(TEST_LEXER)

$(TEST_AST): $(TEST_AST_OBJS) $(LIBFT)
	$(CC) $(TEST_AST_OBJS) $(LIBFT) -o $(TEST_AST)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I includes -I $(LIBFT_DIR) -c $< -o $@
	
$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS) $(TEST_LEXER_OBJS) $(TEST_AST_OBJS) $(TEST_PARSER_OBJS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(TEST_LEXER) $(TEST_AST) $(TEST_PARSER)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all test_lexer test_ast clean fclean re