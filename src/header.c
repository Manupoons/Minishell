/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:32:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/05/26 19:55:29 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void print_banner(void) {
    printf("\033[1;36m");  // Bright cyan
    printf("  __  __ _       _     _          _ _ \n");
    printf(" |  \\/  (_)     (_)   | |        | | |\n");
    printf(" | \\  / |_ _ __  _  __| | ___  __| | |\n");
    printf(" | |\\/| | | '_ \\| |/ _` |/ _ \\/ _` | |\n");
    printf(" | |  | | | | | | | (_| |  __/ (_| |_|\n");
    printf(" |_|  |_|_|_| |_|_|\\__,_|\\___|\\__,_(_)\n");
    printf("\033[0m\n");  // Reset color
}

int handle_space(char *input, int i)
{
    while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n' 
        || input[i] == '\r' || input[i] == '\v' || input[i] == '\f')
        i++;
    return i;
}

// QUOTES

int ft_quotes(char c)
{
    return (c == 34 || c == 39);
}
/*
 * Extrae un token encerrado entre comillas (simples o dobles).
 * 
 * Recibe una línea que comienza con una comilla y extrae el texto
 * entre esa comilla de apertura y la comilla de cierre correspondiente.
 * 
 * Reserva memoria para el token resultante (sin incluir las comillas)
 * y añade un terminador nulo al final.
 * 
 * Retorna la cantidad total de caracteres consumidos en la línea,
 * incluyendo las comillas de apertura y cierre, para que el tokenizer
 * pueda avanzar correctamente.
 * 
 * Devuelve -1 si la comilla de cierre no se encuentra o falla la memoria.
 */

int extract_quoted_token(char *line, char**token)
{
    int     i;
    char    quote;

    quote = line[0]; 
    i = 1;
    while(line[i] && line[i] != quote)
        i++;
    if (!line[i])
        return (-1);
    *token = malloc(sizeof(char) * (i));
    if (!(*token))
        return (-1);
    ft_memcpy(*token, line + 1, i - 1);
    (*token)[i - 1] = '\0';
    return (i + 1);
}

// --------------------










void    add_token(t_shell *mini, t_token_type type, char *line)
{
    t_token *new;
    t_token *current;

    new = (t_token *) malloc(sizeof(t_token));
    if (!new)
        error_message("Failed to alloc mem for token.");
    new->token = ft_strdup(line);
    if (!new->token)
        error_message("Failed to dup line.");
    new->type = type;
    new->next = NULL;
    if (!mini->token)
        mini->token = new;
    else
    {
        current = mini->token;
        while (current->next)
            current = current->next;
        current->next = new;
    }
}
