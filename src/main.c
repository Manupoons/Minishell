#include "./minishell.h"

void    ft_minishell(t_shell *mini)
{
    char    *line;

    while (1)
    {
        line = readline("minishell$ ");
        printf("line %s \n", line);
        tokenizer(mini, line);
        if (!line)
        {
            printf("exit\n");
            break;
        }
        if (*line)
        {
            add_history(line);
            printf("You typed: %s\n", line);
        }
        free(line);
    }
}

int main(int ac, char **av)
{
    t_shell mini;

    if (ac != 1 || av[1])
        return (EXIT_FAILURE);
    print_banner();
    ft_minishell(&mini);
    return (EXIT_SUCCESS);
}


char	**split_line(char *line)
{
	char **args;
	char *token;
	int i = 0;

	args = malloc(sizeof(char *) * 100);
	if (!args)
		return NULL;

	token = strtok(line, " ");
	while (token)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return args;
}