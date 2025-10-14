/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:50:03 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/14 18:47:20 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <libft.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>


// TOKEN
typedef enum e_token_type {
	WORD,			//0 - Mots simples
	PIPE,			//1 - |
	REDIR_IN,		//2 - <
	REDIR_OUT,		//3 - >
	REDIR_APPEND,	//4 - >>
	REDIR_HEREDOC,	//5 - <<
	TOKEN_OR,		//6 - ||
	TOKEN_AND,		//7 - &&
	TOKEN_LPAREN,	//8 - (
	TOKEN_RPAREN,	//9 - )
}	t_token_type;

// QUOTES
typedef enum e_quote_type {
	NO_QUOTE,		// Pas de quotes
	SINGLE_QUOTE,	// '...'
	DOUBLE_QUOTE,	// "..."
}	t_quote_type;

typedef struct s_token {
	t_token_type	type;	// Type du token
	t_quote_type	quote;	// Mode Quote
	char			*str;	// Contenu (malloc)
	struct s_token	*next;	// Liste chaînée
}	t_token;

//LEXER
t_token	*lexer(char *line); 
/* ******************************************************************************* */
/* Liste chaînée de tokens :                                                       */
/* [WORD "echo"] → [WORD "hello"] → [PIPE "|"] → [WORD "cat"] → [WORD "-e"] → NULL */
/* ******************************************************************************  */

// TOKEN
t_token	*create_token(t_token_type type, t_quote_type quote, char *str, int len);
void	token_add_back(t_token **lst, t_token *new);
void	free_tokens(t_token *tokens);
// TOKEN_HANDLER
int	handle_operator(char *line, int *i, t_token **tokens);
int	handle_word(char *line, int *i, t_token **tokens);
int	handle_quotes(char *line, int *i, t_token **tokens);
//TOKEN UTILS
void	skip_spaces(char *line, int *i);
t_token_type	get_operator_type(char *str);
t_quote_type	get_quote_type(char *line, int *i, char *quote_char);

//QUOTES
t_quote_type	get_quote_type(char *line, int *i, char *quote_char);

#endif