#ifndef MINISHELL_H
# define MINISHELL_H

# include <./libft.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termcap.h>
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

typedef struct s_token
{
    int             type;
    char            *token;
    struct  s_token *next; // para recorrer lista
}   t_token;

typedef struct s_redir
{
	char	        *file;
	int            type_cmd; //0: <, 1: >, 2: <<, 3: >>
	struct s_redir  *next;
}	t_redir;

typedef struct s_cmd
{
	char            **argv; // list de comandos
	t_redir         *redir; // lista de redirecciones
	struct s_cmd    *next; // para manejar pipelines (|) entre comandos
} t_cmd;

typedef struct s_env
{
	char *env_name;     // nombre de la variable
	char *env_value;    // valor de la variable
	struct s_env *next; //  siguiente elemento en la lista
}			t_env;

typedef struct s_shell
{
    char    *actual_line;
    t_token *token;
    t_cmd	*arg;
    int  status;
}	t_shell;

//  ###--- MAIN ---### 
void    ft_minishell(t_shell *mini);
void    tokenizer(t_shell *mini, char *line);
//  ###--------------### 
//  ###--- COMMANDS ---###
void	ft_echo(char **argv);
void	ft_env(char **argv);
void	ft_exit(char **argv);
void	ft_pwd(void);
void	ft_comms(char **argv);

//  ###--------------### 

#endif

