#ifndef MINISHELL_H
# define MINISHELL_H

# include <./libft.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termcap.h>
# include <signal.h>
# include "libft.h"


# define HEADER ("\n\033[1;92m\
	███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
	████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
	██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
	██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
	██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
	╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\
	\n\033[0m\
			A simple shell implemented in C                            \n\
	\n\033[0m\
	\t\t --- \033[1;92mmamaratr\033[0m && \033[1;92mjdorazio\033[0m ---\n\
	\n")

typedef struct s_parser t_parser;

typedef enum e_token_type
{
	TOKEN_WORD,       // Palabra normal, comando o argumento
	TOKEN_PIPE,       // '|'
	TOKEN_REDIR_IN,   // '<'
	TOKEN_REDIR_OUT,  // '>'
	TOKEN_APPEND,     // '>>'
	TOKEN_HEREDOC,    // '<<'
	TOKEN_EOF         // Fin de línea o archivo (opcional)
}   t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*token;
	struct s_token	*next; // para recorrer lista
}	t_token;

typedef struct s_arg
{
	char			**argv; // list de comandos
	int				args_count; // cantidad de argumentos
	t_parser		*parser; // lista de redirecciones
	struct s_arg	*next; // para manejar pipelines (|) entre comandos
}	t_arg;

typedef struct s_env
{
	char *env_name;     // nombre de la variable
	char *env_value;    // valor de la variable
	struct s_env *next; //  siguiente elemento en la lista
}	t_env;

typedef struct s_parser 
{
	char			*cmd; // línea de entrada del usuario
	int				fd_in;
	int				fd_out;
	struct s_parser	*next; // estado de salida del comando
}	t_parser;

typedef struct s_shell
{
	char		*actual_line;
	t_token		*tokens;
	t_arg		*arg;
	int			status;
	t_parser	*parser;
	t_env		*env; // lista de variables de entorno
}	t_shell;

//  ###--- MAIN ---###
void    ft_minishell(t_shell *mini);
//  ###--------------### 

//  ###--- HEADER ---### 
void	print_banner(void);
//  ###-------------### 


//  ###--- ERROR_HANDLER ---### 
void	error_message(char *str);
//  ###--------------### 


//  ###--- TOKENIZER ---###
int			handle_space(char *input, int i);
int			handle_quoted_token(char *input, t_token **token_list,  int i);
int 		handle_operator(char *input, t_token **token_list,  int i);
int 		handle_word(char *input, t_token **token_list, int i); // for echo
t_token    *tokenizer(char *input);
//  ###--------------### 

//  ###--- TOKENIZER_UTILS ---### 
int     is_quotes(char c);
int     is_operator(char c);
void    add_token(char *input, t_token **token_list, t_token_type type);
//  ###--------------### 



//  ###--- PARSER ---###
int word_counter(t_token *tokens);
t_arg   *init_arg(int count);
t_arg   *parse_tokens(t_token *token_list);
int handle_word_token(t_arg *arg, char *token, int index);
//  ###--------------### 

char  *ft_read_line(void);


char	**shell_split(t_shell *mini, char *line, char s);
void	ft_next_cmd(t_shell *mini);


void	ft_pwd(t_shell *mini);
void	ft_exit(t_shell *mini);
void	ft_echo(t_shell *mini);
int		is_comms(t_shell *mini);
void	ft_comms(t_shell *mini);

#endif

