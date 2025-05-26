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


typedef struct s_redir
{
	char	*file;
	int		type; //0: <, 1: >, 2: <<, 3: >>
	struct s_redir *next;
}	t_redir;

typedef struct s_arg
{
	char	**cmds; // list de comandos
	t_redir	*redir_in; // lista de redirecciones
	struct s_arg	*next; // para manejar pipelines (|) entre comandos
} t_arg;

typedef struct s_shell
{
	t_arg	*arg;
}	t_shell;



//  ###--- MAIN ---### 
void    ft_minishell(t_shell mini, char **env);
//  ###--------------### 



//  ###--- HEADER ---### 
void	print_header(void);
//  ###--------------### 


#endif
