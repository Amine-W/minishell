/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 08:54:10 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/22 11:34:54 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parse_command(t_token *tokens, int length)
{
	int			count;
	char		**argv;
	t_redir		*head_redir;
	t_command	*command;

	head_redir = NULL;
	count = count_tokens_word(tokens, length);
	argv = create_argv(tokens, count, length);
	if (!argv)
		return (NULL);
	head_redir = parse_redirections(tokens, length);
	command = malloc(sizeof(t_command));
	if (!command)
		return (free_redirections(head_redir), ft_free_split(argv), NULL);
	command->argv = argv;
	command->redirections = head_redir;
	return (command);
}

t_redir_type	token_to_redir_type(t_token_type type)
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
