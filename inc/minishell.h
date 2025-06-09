/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:15:39 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/09 18:32:44 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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

#define READLINE_MSG "\001\033[1;36m\002minishell\001\033[34m\002$> \001\033[0m\002"

extern int	g_signal;
typedef enum e_signal
{
	S_BASE,						//Señal base
	S_HEREDOC,					//entra heredoc
	S_HEREDOC_END,				//fin heredoc
	S_HEREDOC_CANCEL,			//Ctrl + D en heredoc
	S_SIGINT,					//Ctrl + C
	S_SIGINT_CMD,				//Ctrl + C en medio de comando
	S_CMD,						//se ejecuta comando
	S_SIZE
}	t_signal;

typedef enum e_token_type
{
	TOKEN_WORD,					// Palabra normal, comando o argumento
	TOKEN_PIPE,					// '|'
	TOKEN_REDIR_IN,				// '<'
	TOKEN_REDIR_OUT,			// '>'
	TOKEN_APPEND,				// '>>'
	TOKEN_HEREDOC,				// '<<'
	TOKEN_EOF					// Fin de línea o archivo (opcional)
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*token;
	struct s_token	*next;		// para recorrer lista
}	t_token;

typedef struct s_redir
{
	char			*cmd;		// línea de entrada del usuario
	int				fd_in;
	int				fd_out;
	int				type;		// redirection type
	struct s_redir	*next;		// estado de salida del comando
}	t_redir;

typedef struct s_arg
{
	char			**argv;		// list de comandos
	int				args_count;	// cantidad de argumentos
	t_redir			*redirs;	// lista de redirecciones
	int				pipe_in;	//fd de pipes
	int				pipe_out;	//fd de pipes
	struct s_arg	*next;		// para manejar pipelines (|) entre comandos
	struct s_arg	*prev;		// para controlar previo a pipes
}	t_arg;

typedef struct s_env
{
	char			*env_name;	// nombre de la variable
	char			*env_value;	// valor de la variable
	struct s_env	*next;		// siguiente elemento en la lista
}	t_env;

typedef struct s_shell
{
	char		*actual_line;
	t_token		*tokens;
	t_arg		*arg;
	int			status;
	t_env		*env;			// lista de variables de entorno
}	t_shell;

//###--- BUILTINS ---###
int		is_comms(t_shell *mini);
void	ft_comms(t_shell *mini);
void	ft_pwd(t_shell *mini);
void	ft_cd(t_shell *mini);
void	ft_env(t_shell *mini);
void	ft_exit(t_shell *mini);
void	ft_echo(t_shell *mini);
void	ft_export(t_shell *mini);
void	ft_unset(t_shell *mini);
//###----------------###

//###--- BUILTINS_UTILS ---###
int		check_export(char *argv);
void	add_arg_to_env(char *var, t_shell *mini);
//###----------------------###

//###--- CMD ---###
void	ft_cmd_exec(t_shell *mini);
//###-----------###

//###--- CMD_UTILS ---###
bool	has_stdout_redirection(t_redir *redir);
bool	init_pipes(t_shell *mini);
int		close_pipes(t_arg *current, int prev_fd_in);
void	execute_redir(t_shell *msh);
void	handle_status(t_shell *mini);
void	execute_pipeline_commands(t_shell *mini, pid_t *last_pid);
void	execute_redir_token(t_arg *args);
void	child_process(t_shell *msh);
//###-----------------###


//###--- PARSER ---###
t_arg	*parse_tokens(t_token *tokens);
void	handle_redir_token(t_arg *curr_arg, t_token *token);
//###--------------###

//###--- PARSER_UTILS---###
int		word_counter(t_token *tokens);
t_arg	*init_arg(int count);
int		is_redir(int type);
//###-------------------###

//###--- SIGNAL ---###
void	init_signal(void);
//###--------------###

//###--- TOKENIZER ---###
int		handle_quoted_token(char *input, t_token **token_list, int i);
int		handle_operator(char *input, t_token **token_list, int i);
int		handle_word(char *input, t_token **token_list, int i);
t_token	*tokenizer(char *input);
//###-----------------###

//###--- TOKENIZER_UTILS ---###
int		is_quotes(char c);
int		is_operator(char c);
int		is_space(char c);
int		handle_space(char *input, int i);
void	add_token(char *input, t_token **token_list, t_token_type type);
//###-----------------------###

//###--- MINISHELL_UTILS ---###
	void ft_add_back_env(t_env **lst, t_env * new);
	t_env	*ft_lst_new_env(char *name, char *value);
	t_env	*get_env_node(t_env *env, const char *name);
	void ft_lst_env_init(t_shell * mini, char **envp);
	char *get_env_name(char *name);
	char *get_env_value(char *value);
//###-----------------------###
void	error_message(char *str);
//###-----------------------###
void	ft_free_env(t_env **env);
void	ft_free_list(t_env **env);
void	free_tokens(t_token *tokens);
void	free_redirs(t_redir *redirs);
void	free_args(t_arg *args);
//###-----------------------###
char	*ft_get_path(char *cmd, t_env *env);
char	**ft_env_to_array(t_shell *mini);
//###-----------------------###

//###--- DEBUGGIN ---###
void	print_parser(t_arg *head);
void	print_tokens(t_token *tokens);

#endif