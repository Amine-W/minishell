/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:12:01 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/20 15:38:06 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_operator_info	find_operator(t_token *tokens, int length, t_operator_prio prio)
{
	int				count;
	int				last_op_position;
	int				i;
	t_token_type	last_op_type;
	t_token			*current;

	last_op_position = -1;
	last_op_type = 0;
	count = 0;
	i = 0;
	current = tokens;
	while (current && i < length)
	{
		if (current->type == TOKEN_LPAREN)
			count++;
		else if (current->type == TOKEN_RPAREN)
			count--;
		if (count == 0 && is_target_operator(current->type, prio))
		{
			last_op_position = i;
			last_op_type = current->type;
		}
		current = current->next;
		i++;
	}
	return ((t_operator_info){last_op_position, last_op_type});
}

int	has_wrapping_parentheses(t_token *tokens, int length)
{
	t_token	*current;
	int		i;
	int		count;

	if (tokens->type != TOKEN_LPAREN)
		return (0);
	current = tokens;
	i = 0;
	while (i++ < length - 1 && current)
		current = current->next;
	if (current->type != TOKEN_RPAREN)
		return (0);
	current = tokens;
	count = 0;
	i = 0;
	while (i < length - 1)
	{
		count += (current->type == TOKEN_LPAREN);
		count -= (current->type == TOKEN_RPAREN);
		if (count == 0 && i < length - 1)
			return (0);
		current = current->next;
		i++;
	}
	return (1);
}

int	is_target_operator(t_token_type type, t_operator_prio prio)
{
	if (prio == LOW_PRIO)
		return (type == TOKEN_OR || type == TOKEN_AND);
	else if (prio == MEDIUM_PRIO)
		return (type == TOKEN_PIPE);
	return (0);
}
