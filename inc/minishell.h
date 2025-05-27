#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termcap.h>
# include "libft.h"


// SE LO PEDI A CHATGPT me dio pereza generarlo
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
    t_token_type    type;
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

//  ###--- HEADER ---### 
void	print_banner(void);
//  ###-------------### 


//  ###--- HEADER ---### 
int ft_isspace(char c);
int ft_quotes(char c);
int extract_quoted_token(char *line, char**token);
int ft_special_simbol(char *line);

//  ###--------------### 

//  ###--- ERROR_HANDLER ---### 
void	error_message(char *str);


//  ###--------------### 


#endif

