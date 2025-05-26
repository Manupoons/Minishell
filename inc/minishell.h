#ifndef MINISHELL_H
# define MINISHELL_H

# include <./libft.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <sys/ioctl.h>

//commands

void    exec_comms(char **argv);
void    exec_ls(char **argv);
void    exec_cd(char **argv);
int    exec_pwd(void);
void    exec_echo(char **argv);

#endif