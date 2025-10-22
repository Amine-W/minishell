/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:08:43 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/22 11:41:02 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*current;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

char	**create_argv(t_token *tokens, int count, int length)
{
	char	**argv;
	int		i;
	t_token	*current;

	argv = malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	current = tokens;
	while (current && i < length)
	{
		if (current->type == TOKEN_LPAREN || current->type == TOKEN_RPAREN)
			return (argv[i] = NULL, ft_putstr_fd
				("minishell: syntax error near unexpected token `('\n", 2),
				ft_free_split(argv), NULL);
		if (current->type == TOKEN_WORD)
		{
			argv[i++] = ft_strdup(current->str);
			if (!argv[i - 1])
				return (ft_free_split(argv), NULL);
		}
		current = current->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	count_tokens_word(t_token *token, int length)
{
	int		count;
	t_token	*current;
	int		i;

	i = 0;
	count = 0;
	current = token;
	while (current && i < length)
	{
		if (current->type == TOKEN_WORD)
			count++;
		current = current->next;
		i++;
	}
	return (count);
}

t_redir	*parse_redirections(t_token *tokens, int length)
{
	t_token	*current;
	t_redir	*redir;
	t_redir	*head_redir;

	current = tokens;
	head_redir = NULL;
	while (current && length--)
	{
		if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_REDIR_HEREDOC || current->type
			== TOKEN_REDIR_APPEND)
		{
			redir = malloc(sizeof(t_redir));
			if (!redir)
				return (NULL);
			redir->type = token_to_redir_type(current->type);
			redir->file = ft_strdup(current->next->str);
			redir->next = NULL;
			redir_add_back(&head_redir, redir);
			current = current->next;
		}
		current = current->next;
	}
	return (head_redir);
}

void	free_redirections(t_redir *redirections)
{
	t_redir	*current;
	t_redir	*temp;

	if (!redirections)
		return ;
	current = redirections;
	while (current)
	{
		temp = current->next;
		free(current->file);
		free(current);
		current = temp;
	}
	return ;
}
