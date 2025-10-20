/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:47:17 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/20 13:26:31 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parse(t_token *tokens, int length)
{
	t_operator_info	operator_info;
	t_node			*node;
	t_token			*tokens_right;
	t_command		*command;
	int				len_right;
	
	if (tokens == NULL || length == 0)
		return (NULL);
	len_right = 0;
	node = NULL;
	operator_info = find_operator(tokens, length, LOW_PRIO);
	if (operator_info.position != -1)
	{
		if (operator_info.type == TOKEN_AND)
			node = create_node(NODE_AND, NULL);
		else if (operator_info.type == TOKEN_OR)
			node = create_node(NODE_OR, NULL);
			
		node->left = parse(tokens, operator_info.position);
		
		tokens_right = advance_token(tokens, operator_info.position + 1);
		len_right = length - operator_info.position - 1;
		node->right = parse(tokens_right, len_right);
		return (node);
	}
	operator_info = find_operator(tokens, length, MEDIUM_PRIO);
	if (operator_info.position != -1)
	{
		node = create_node(NODE_PIPE, NULL);
		
		node->left = parse(tokens, operator_info.position);
		
		tokens_right = advance_token(tokens, operator_info.position + 1);
		len_right = length - operator_info.position - 1;
		node->right = parse(tokens_right, len_right);
		return (node);
	}
	if (has_wrapping_parentheses(tokens, length))
		return (parse(tokens->next, length - 2));
	command = parse_command(tokens);
	node = create_node(NODE_COMMAND, command);
	return (node);
}
