#include "./minishell.h"

// void    parse(char *tokens)
// {
//     // función parse(tokens):
//     // crear lista vacía de comandos
//     // crear nuevo comando actual

//     // para cada token en tokens:
//     //     si es PIPE:
//     //         guardar comando actual
//     //         crear nuevo comando

//     //     si es WORD:
//     //         añadir a argv del comando actual

//     //     si es redirección:
//     //         el siguiente token debe ser un archivo
//     //         añadir a lista de redirecciones

//     // añadir último comando a lista
//     // devolver lista de comandos
// }


int ft_isspace(char c) // mejorar
{
    return (c == " ");
}

int ft_comillas(char c)
{
    return (c == 34 || c == 39);
}

int ft_extract_quoted_token(char *line)
{
    int i;
    int j;
    char    *temp;

    i = 1;
    j = 0;
    while (!ft_comillas(line[i]))
    {
        temp[i] = line[i];
        i++;
        j++;    
    }
}


void    tokenizer(t_shell *mini, char *line)
{
    int     i;
    char    *temp;

    i = 0;
    while (line[i])
    {
        if (ft_isspace(line[i]))
            i++;
        if (ft_comillas(line[i]))
            ft_extract_quoted_token(&line);
    }
}



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

void	print_banner(void) {
	printf("\033[1;36m");  // Bright cyan
	printf(" __  __ _       _     _          _ _ \n");
	printf("|  \\/  (_)_ __ (_)___| |__   ___| | |\n");
	printf("| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n");
	printf("| |  | | | | | | \\__ \\ | | |  __/ | |\n");
	printf("|_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\n");
	printf("                                     \n");
	printf("\033[0m\n");  // Reset color
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