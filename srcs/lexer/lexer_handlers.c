/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:51:41 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/14 19:28:52 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_operator(char *line, int *i, t_token **tokens)
{
	t_token_type	type;
	t_token			*token;
	int				len;

	type = get_operator_type(&line[*i]);
	if (type == REDIR_APPEND || type == REDIR_HEREDOC
		|| type == TOKEN_OR || type == TOKEN_AND)
		len = 2;
	else
		len = 1;
	token = create_token(type, NO_QUOTE, &line[*i], len);
	if (!token)
		return (-1);
	token_add_back(tokens, token);
	(*i) += len;
	return (0);
}

int	handle_word(char *line, int *i, t_token **tokens)
{
	int		j;
	int		len;
	t_token	*token;
	
	j = *i;
	while (!ft_isspace(line[j]) && !ft_isdelimiter(line[j]) && line[j] != '"' && line[j] != '\'' && line[j] != '\0')
		j++;
	len = j - *i;
	token = create_token(WORD, NO_QUOTE, &line[*i], len);
	if (!token)
		return (-1);
	token_add_back(tokens, token);
	*i = j;
	return (0);
}

int	handle_quotes(char *line, int *i, t_token **tokens)
{
	t_quote_type	quote_type;
	t_token			*token;
	char			quote_char;
	int				j;
	int				len;

	quote_type = get_quote_type(line, i, &quote_char);
	j = (*i);
	(*i)++;
	while(line[*i] != quote_char && line[*i] != '\0')
		(*i)++;
	if(line[*i] == '\0')
		return (-1);
	len = *i - j + 1;
	token = create_token(WORD, quote_type, &line[j], len);
	if(!token)
		return (-1);
	token_add_back(tokens, token);
	(*i)++;
	return (0);
}
