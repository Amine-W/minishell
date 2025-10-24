/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:50:03 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/23 18:14:14 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <libft.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>


/* ================================= QUOTES ====================================*/

typedef enum e_quote_type {
	NO_QUOTE,		// Pas de quotes
	SINGLE_QUOTE,	// '...'
	DOUBLE_QUOTE,	// "..."
}	t_quote_type;

/* ============================ TOKEN ============================== */

typedef enum e_token_type {
	TOKEN_WORD,				//0 - Mots simples
	TOKEN_PIPE,				//1 - |
	TOKEN_REDIR_IN,			//2 - <
	TOKEN_REDIR_OUT,		//3 - >
	TOKEN_REDIR_APPEND,		//4 - >>
	TOKEN_REDIR_HEREDOC,	//5 - <<
	TOKEN_OR,				//6 - ||
	TOKEN_AND,				//7 - &&
	TOKEN_LPAREN,			//8 - (
	TOKEN_RPAREN,			//9 - )
	TOKEN_ERROR,			//10 ERROR
}	t_token_type;


typedef struct s_token {
	t_token_type	type;	// Type du token
	t_quote_type	quote;	// Mode Quote
	char			*str;	// Contenu (malloc)
	struct s_token	*next;	// Liste chaînée
}	t_token;

/*================================= REDIR ========================================*/

typedef enum e_redir_type {
	REDIR_NONE,
	REDIR_IN,		//2 - <
	REDIR_OUT,		//3 - >
	REDIR_APPEND,	//4 - >>
	REDIR_HEREDOC,	//5 - <<
}	t_redir_type;

typedef struct s_redir {
	t_redir_type	type;	// Type de redirections
	char			*file;	// Nom du fichier cible
	struct s_redir	*next; // Liste chaînée
}	t_redir;

/*================================== COMMANDES ====================================*/

typedef struct s_command {
	char			**argv;			// Tableau : ["cmd", "arg1", ..., NULL]
	t_redir			*redirections;	// {REDIR_TYPE, "file", next}
} t_command;

/*==================================== AST NODE ======================================*/

typedef enum e_node_type {
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
}	t_node_type;

typedef struct s_node {
	t_node_type		type;
	t_command		*command;	// Pour NODE_COMMAND
	struct s_node	*left;		// Pour opérateur
	struct s_node	*right;		// Pour opérateur
}	t_node;

/*======================================== OPERATEURS ===================================*/

typedef enum e_operator_prio {
	LOW_PRIO,
	MEDIUM_PRIO,
}	t_operator_prio;


typedef struct s_operator_info {
	int				position;	// Position de l'opérateur trouvé dans la liste
	t_token_type	type;		// TOKEN_OR, TOKEN_AND, ...
	
}	t_operator_info;

/*==================================================================================*/
/*============================= FONCTIONS ==========================================*/
/*==================================================================================*/

/*================================ LEXER ===========================================*/

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


/*======================================= AST =============================================*/

// NODE
t_node	*create_node(t_node_type type, t_command *command);
int		count_nodes(t_node *node);

// AST UTILS
void	print_ast(t_node *node, int depth);
void	free_ast(t_node *node);
void	free_redirections(t_redir *redirections);

/*====================================== PARSING ===========================================*/

t_node	*parse(t_token *tokens, int length);

// PARSE COMMAND
t_command		*parse_command(t_token *tokens, int length);

// PARSE COMMAND UTILS
char			**create_argv(t_token *tokens, int count, int length);
t_redir			*parse_redirections(t_token *tokens, int length);
void			redir_add_back(t_redir **lst, t_redir *new);



// UTILS
t_operator_info	find_operator(t_token *tokens, int length, t_operator_prio prio);
int				has_wrapping_parentheses(t_token *tokens, int length);
int				is_target_operator(t_token_type type, t_operator_prio prio);
t_node			*handle_operator_parser(t_token *tokens, int length, 
					t_operator_info operator_info);
t_node			*create_command_node(t_token *tokens, int length);
void			print_syntax_error(char *token);



// TOKENS
int				ft_tokens_size(t_token *lst);
int				count_tokens_word(t_token *token, int length);
t_redir_type	token_to_redir_type(t_token_type type);
t_token			*advance_token(t_token *token, int position);


/*========================================= EXEC ===============================================*/

int	exec_ast(t_node *node);
int	exec_pipeline(t_node *node);
int	exec_command(t_command *cmd, char **envp);


// PATH
char	*get_path(char *cmd, char **envp);
char	*find_path_in_env(char **envp);
char	*try_path(char **paths, char *cmd);

// UTILS
void	print_command_error(char *cmd, int error_type);

#endif