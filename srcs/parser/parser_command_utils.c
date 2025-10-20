/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 09:08:43 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/20 11:38:06 by amwahab          ###   ########.fr       */
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

char	**create_argv(t_token *tokens, int count)
{
	char	**argv;
	int		i;
	t_token	*current;
	
	argv = malloc(sizeof(char*) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			{
				argv[i] = ft_strdup(current->str);
				if(!argv[i])
					return (NULL);
				i++;
			}
		current = current->next;
	}
	argv[i] = NULL;
	return (argv);
}

int	count_tokens_word(t_token *token)
{
	int		count;
	t_token	*current;

	count = 0;
	current = token;
	while(current)
	{
		if (current->type == TOKEN_WORD)
			count++;
		current = current->next;
	}
	return (count);
}

t_redir	*parse_redirections(t_token *tokens)
{
	t_token	*current;
	t_redir	*redir;
	t_redir	*head_redir;

	head_redir = NULL;
	current = tokens;
	while(current)
	{
		if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_REDIR_OUT
				|| current->type == TOKEN_REDIR_HEREDOC || current->type == TOKEN_REDIR_APPEND)
		{
			redir = malloc(sizeof(t_redir));
			if(!redir)
				return (NULL);
			redir->type = token_to_redir_type(current->type);
			redir->file = ft_strdup(current->next->str);
			redir->next = NULL;
			redir_add_back(&head_redir, redir);
			current = current->next;
		}
		current = current->next;
	}
	return(head_redir);
}

void	free_redirections(t_redir *redirections)
{
	t_redir	*current;
	t_redir *temp;
	
	if(!redirections)
		return ;
	current  = redirections;
	while (current)
	{
		temp = current->next;
		free(current->file);
		free(current);
		current = temp; 
	}
	return ;
}