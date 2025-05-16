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
# include <./libft.h>

//commands

void    exec_comms(char **argv);
void    exec_ls(char **argv);
void    exec_cd(char **argv);
void    exec_pwd(char **argv);
void    exec_echo(char **argv);

#endif