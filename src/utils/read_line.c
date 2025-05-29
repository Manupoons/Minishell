#include "./minishell.h"

char  *ft_read_line(void)
{
  char  *line;
  
  line = readline("minishell$ ");
  if (*line && line)
    add_history(line);
  return (line);
}