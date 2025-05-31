/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:15:39 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/31 12:24:59 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <./libft.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <libgen.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

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

# define READLINE_MSG "\033[1;36mminishell\033[34m$> \033[0m"

extern int	g_signal;

typedef enum e_signal
{
	S_BASE,				//Señal base
	S_HEREDOC,			//entra heredoc
	S_HEREDOC_END,		//fin heredoc
	S_HEREDOC_CANCEL,	//Ctrl + D en heredoc
	S_SIGINT,			//Ctrl + C
	S_SIGINT_CMD,		//Ctrl + C en medio de comando
	S_CMD,				//se ejecuta comando
	S_SIZE
}	t_signal;

typedef enum e_token_type
{
	TOKEN_WORD,       // Palabra normal, comando o argumento
	TOKEN_PIPE,       // '|'
	TOKEN_REDIR_IN,   // '<'
	TOKEN_REDIR_OUT,  // '>'
	TOKEN_APPEND,     // '>>'
	TOKEN_HEREDOC,    // '<<'
	TOKEN_EOF         // Fin de línea o archivo (opcional)
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*token;
	struct s_token	*next; // para recorrer lista
}	t_token;

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

typedef struct s_cmd
{
	char			**argv; // list de comandos
	int				args_count; // cantidad de argumentos
	t_parser		*parser; // lista de redirecciones
	struct s_cmd	*next; // para manejar pipelines (|) entre comandos
}	t_cmd;

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
//void    ft_minishell(t_shell *mini);
//  ###--------------### 

//  ###--- HEADER ---### 
void	print_banner(void);
//  ###-------------### 

//  ###--- HEADER ---### 
int		ft_isspace(char c);
int		is_quotes(char c);
//  ###--------------### 

//  ###--- ERROR_HANDLER ---### 
void	error_message(char *str);
//  ###--------------### 


//  ###--- TOKENIZER ---###
int		handle_space(char *input, int i);
int		handle_quoted_token(char *input, t_shell *mini, int i);
int		handle_operator(char *input, t_shell *mini, int i);
int		handle_word(char *input, t_shell *mini, int i);
void	tokenizer(t_shell *mini, char *input);
//  ###--------------### 

//  ###--- TOKENIZER_UTILS ---### 
int		ft_quotes(char c);
int		is_operator(char c);
void	add_token(char *input, t_shell *mini, t_token_type type);
//  ###--------------### 

//  ###--- MINISHELL_UTILS ---###
char	**ft_env_to_array(t_shell *mini);

//  ###-------------------###

char	**shell_split(t_shell *mini, char *line, char s);
void	ft_cmd_exec(t_shell *mini);

void	ft_pwd(t_shell *mini);
void	ft_cd(t_shell *mini);
void	ft_env(t_shell *mini);
void	ft_exit(t_shell *mini);
void	ft_echo(t_shell *mini);
void	ft_export(t_shell *mini);
//void	ft_unset(t_shell *mini);

int		is_comms(t_shell *mini);
void	ft_comms(t_shell *mini);

char	*get_env_name(char *name);
char	*get_env_value(char *value);
void	ft_add_back_env(t_env **lst, t_env *new);
void	ft_lst_env_init(t_env **env, char **envp);
t_env	*ft_lst_new_env(char *name, char *value, int alloc);

char	*ft_get_path(char *cmd, t_env *env);
void	ft_free_env(t_env **env);
void	ft_free_list(t_env **env);
void	add_arg_to_env(char *var, t_shell *mini);

void	init_signal(void);

#endif
