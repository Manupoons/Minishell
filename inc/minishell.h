/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 12:15:39 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/11 08:31:29 by jdorazio         ###   ########.fr       */
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
	char			quote_type;
	struct s_token	*next;		// para recorrer lista
}	t_token;

typedef struct s_redir
{
	char			*cmd;		// línea de entrada del usuario
	int				type;		// redirection type
	struct s_redir	*next;		// estado de salida del comando
}	t_redir;

typedef struct s_arg
{
	char			**argv;		// list de comandos
	int				args_count;	// cantidad de argumentos
	t_redir			*redirs;	// lista de redirecciones
	int				fd_in; 
	int				fd_out;
	int				pipe_in;
	int				pipe_out; 
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
	bool		in_pipe;
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
bool	init_pipes(t_shell *mini);
void	close_pipes(t_arg *current);
int	execute_redir(t_arg *arg);
void	handle_status(t_shell *mini);
void	execute_pipeline_commands(t_shell *mini, pid_t *last_pid);
void	child_process(t_shell *msh);
//###-----------------###


//###--- PARSER ---###
t_arg	*parse_tokens(t_token *tokens, t_env *env, int *status);
//###--------------###

//###--- PARSER_UTILS---###
t_arg	*init_arg(void);
int		is_redir(int type);
void	append_to_parser(t_redir **head, t_redir *redir);
char	**ft_add_to_argv(char **arr, char *new_str);
void	split_tokens(char **expanded, t_arg **curr);
//###-------------------###

//###--- EXPAND_VAR ---###
char	*expand(t_token *token, t_env *env, int *status, int *flag);
//###-----------------------###

//###--- EXPAND VAR UTILS---###
char	*ft_join_free(char *dst, char *src);
char	*strjoin_char(char *s, char c);
//###--- PARSER_UTILS---###


//###--- SIGNAL ---###
void	init_signal(void);
//###--------------###

//###--- TOKENIZER ---###
char	*handle_quoted_token(char *input, int *i, char quote);
int		handle_operator(char *input, t_token **token_list, int i);
char	*handle_word(char *input, int *i);
t_token	*tokenizer(char *input, int *status);
//###-----------------###

//###--- TOKENIZER_UTILS ---###
int		is_quotes(char c);
int		is_operator(char c);
int		is_space(char c);
int		handle_space(char *input, int i);
void	add_token(char *input, t_token **token_list, t_token_type type, char quote);
//###-----------------------###

//###--- TOKENIZER_UTILS 2 ---###
int		is_quotes(char c);
int		is_operator(char c);
int		is_space(char c);
int		handle_space(char *input, int i);
void	add_token(char *input, t_token **token_list, t_token_type type, char quote);
//###-----------------------###

//###--- ENV UTILS ---###
void	ft_add_back_env(t_env **lst, t_env *new);
t_env	*ft_lst_new_env(char *name, char *value);
void	ft_lst_env_init(t_shell *mini, char **envp);
char	*get_env_name(char *name);
char	*get_env_value(char *value);
char	*get_env_value_by_name(t_env *env, const char *name);
void	update_shlvl(t_shell *mini);


//###-----------------------###

//###--- MINISHELL_UTILS ---###
char	*extract_single_quotes(char *input, int *i);
char	*extract_double_quotes(char *input, int *i);
char	*handle_quoted_token(char *input, int *i, char quote);
char	*handle_word(char *input, int *i);
//###-----------------------###

//###--- MINISHELL_UTILS ---###
char	*generate_tmp_filename(void);
int	handle_heredoc(t_arg *arg, t_redir *redir);
int	open_infile(t_arg *arg, t_redir *redir);
int	open_outfile(t_arg *arg, t_redir *redir);
int	open_append(t_arg *arg, t_redir *redir);

//###-----------------------###



//###-----------------------###
void	ft_free_env(t_env **env);
void	ft_free_list(t_env **env);
void	free_tokens(t_token *tokens);
void	free_redirs(t_redir *redirs);
void	free_args(t_arg *args);
void	free_array(char **arr);
t_arg	*handle_parse_errors(t_arg *head_arg, t_arg *curr_arg);
//###-----------------------###
char	*ft_get_path(char *cmd, t_env *env);
char	**ft_env_to_array(t_shell *mini);
//###-----------------------###

//###--- DEBUGGIN ---###
// void	print_parser(t_arg *head);
void	print_tokens(t_token *tokens);
void	free_array_split(char **arr);
void	print_parser(t_arg *head);

int build_compound_token(char *input, int i, t_token **token_list);
int process_fragment(char **full, char *frag, char *last_q, t_token **token_list);
char current_quote_type(char *str);
char *get_fragment(char *input, int *i);
int build_assignment_token(char *input, int i, t_token **token_list);
int handle_compound_words(char *input, t_token **token_list, int i);
int is_assignment(char *input);


#endif
