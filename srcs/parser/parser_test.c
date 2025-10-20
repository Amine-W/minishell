/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:14:44 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/20 15:15:59 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char	*input;
	t_token	*tokens;
	t_node	*ast;
	int		length;

	printf("\n========== TEST 1 : cat file.txt ==========\n");
	input = "(cat file.txt)";
	tokens = lexer(input);
	length = ft_tokens_size(tokens);
	ast = parse(tokens, length);
	print_ast(ast, 0);
	free_ast(ast);

	printf("\n========== TEST 2 : (cat < input.txt | grep test > output.txt) && echo success || (ls -la  ==========\n");
	input = "(cat < input.txt | grep test > output.txt) && echo success || (ls -la && pwd)";
	tokens = lexer(input);
	length = ft_tokens_size(tokens);
	ast = parse(tokens, length);
	print_ast(ast, 0);
	free_ast(ast);

	printf("\n========== TEST 3 : cat < in.txt > out.txt ==========\n");
	input = "cat < in.txt > out.txt";
	tokens = lexer(input);
	length = ft_tokens_size(tokens);
	ast = parse(tokens, length);
	print_ast(ast, 0);
	free_ast(ast);

	return (0);
}