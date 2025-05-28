#include "./minishell.h"


void    ft_init_shell(t_shell *mini, char **envp)
{

}

void    ft_minishell(t_shell *mini)
{
    char    *line;
    
    while(1)
    {
        line = ft_read_line(); // readline + history
        if (!line)
            break;
        mini->token = tokenizer(line); // tokenizador de palabaras
        // mini->cmds = parse_tokens(mini->tokens); // parser: agrupa tokens en comandos
        // ft_execute_cmds(mini); // ejecuta los comandos (Fork / Builtin)
        // ft_cleanup_cycle(mini); //  libera tokens, cmds , line
    }
    free(line);
}


int main(int ac, char **av)
{
	t_shell	mini;

	if (ac != 1 || av[1])
		return (EXIT_FAILURE);
	printf("%s", HEADER);
	//ft_init_shell(&mini, envp);
	ft_minishell(&mini);
	return (EXIT_SUCCESS);
}
