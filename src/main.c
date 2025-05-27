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


int ft_isspace(char c) // mejorar		printf("line %s \n", line);

{
	return (c == ' ');
}

int ft_comillas(char c)
{
	return (c == 34 || c == 39);
}

void ft_extract_quoted_token(char *line)
{
	int i;
	int j;
	char    *temp;

	i = 1;
	j = 0;
	temp = malloc(sizeof(char));
	while (!ft_comillas(line[i]))
	{
		temp[i] = line[i];
		i++;
		j++;
	}
}

void	tokenizer(t_shell *mini, char *line)
{
	int	i;
	//char    *temp;
	(void)mini;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		if (ft_comillas(line[i]))
			ft_extract_quoted_token(line);
	}
}

int main(int ac, char **av)
{
	t_shell	mini;

	if (ac != 1 || av[1])
		return (EXIT_FAILURE);
	printf("%s", HEADER);
	ft_minishell(&mini);
	return (EXIT_SUCCESS);
}
