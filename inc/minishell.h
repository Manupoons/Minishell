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


typedef struct s_shell
{
    char    *actual_line;
    t_token *token;
    t_cmd	*arg;
    int  status;
}	t_shell;

//  ###--- MAIN ---### 
void    ft_minishell(t_shell *mini);
void    tokenizer(t_shell *mini);
//  ###--------------### 

//  ###--- HEADER ---### 
void	print_banner(void);
//  ###--------------### 

#endif

