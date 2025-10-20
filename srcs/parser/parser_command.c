/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:54:10 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/20 11:36:12 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *parse_command(t_token *tokens)
{
	int			count;
	char		**argv;
	t_redir		*head_redir;
	t_command	*command;

	head_redir = NULL;
	count = count_tokens_word(tokens);
	argv = create_argv(tokens, count);
	if(!argv)
		return (NULL);
	head_redir = parse_redirections(tokens);
	command = malloc(sizeof(t_command));
	if(!command)
		return (NULL);
	command->argv = argv;
	command->redirections = head_redir;
	return(command);
}

t_redir_type token_to_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	if (type == TOKEN_REDIR_HEREDOC)
		return (REDIR_HEREDOC);
	return (REDIR_NONE);
}

