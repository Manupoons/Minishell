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

typedef struct s_cmd
{
	char			**argv; // list de comandos
	int				args_count; // cantidad de argumentos
	t_parser		*parser; // lista de redirecciones
	struct s_cmd	*next; // para manejar pipelines (|) entre comandos
}	t_cmd;

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
	t_token		*token;
	t_cmd		*arg;
	int			status;
	t_parser	*parser;
	t_env		*env; // lista de variables de entorno
}	t_shell;

//  ###--- MAIN ---###
void    ft_minishell(t_shell *mini);
void    tokenizer(t_shell *mini, char *line);
//  ###--------------###

//  ###--- COMMANDS ---###
void	ft_echo(t_shell *mini);
void	ft_env(t_shell *mini);
void	ft_exit(t_shell *mini);
void	ft_pwd(t_shell *mini);

int		is_comms(t_shell *mini);
void	ft_comms(t_shell *mini);

//  ###--------------###

#endif

