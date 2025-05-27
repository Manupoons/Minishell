/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:41:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/05/27 19:13:27 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int handle_space(char *input, int i)
{
    while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n' 
        || input[i] == '\r' || input[i] == '\v' || input[i] == '\f')
        i++;
    return (i);
}

int handle_quoted_token(char *input, t_shell *mini, int i)
{
    char    *str;
    char    quote;
    int     j;
    int     len;

    quote = input[i];     // esto confirma que la quote que finalice el loop sean iguales
    j = 1 + i;
    while (input[j] != quote && input[j]) // solo sale si las loops son iguales
        j++;
    if (input[j] == '\0')
        error_message("missing closing quotes.");
    len = j -  i - 1;
    str = malloc(len + 1);    
    if (!str)
        error_message("failed to alloc mem.");
    ft_strlcpy(str, input + i + 1, len + 1); // revisar esta funcion porque esta returns input
    add_token(str, mini, TOKEN_WORD);
    return (j - i + 1);
}

int handle_operator(char *input, t_shell *mini, int i)
{
    if (input[i] == '|')
    {
        return (add_token("|", mini, TOKEN_PIPE), 1);
    }
    else if (input[i] == '<')
    {
        if (input[i + 1] == '<')
            return (add_token("<<", mini, TOKEN_HEREDOC), 2); 
        return (add_token("<", mini, TOKEN_REDIR_IN), 1); 

    }
    else if (input[i] == '>')
    {
        if (input[i + 1] == '>')
            return (add_token(">>", mini, TOKEN_APPEND), 2);
        return (add_token(">", mini, TOKEN_REDIR_OUT), 1); 
    }
    return (0);
}

int handle_word(char *input, t_shell *mini, int i) // for echo
{
    int     start;
    int     len;
    char    *str;

    start = i;
    while (input[i] && !(is_quotes(input[i])) && !(is_operator((input[i]))))
        i++;
    len = i - start;
    str = malloc(len + 1);
    if (!str)
        error_message("failed to alloc mem.");
    ft_strlcpy(str, input + start, len + 1);
    add_token(str, mini, TOKEN_WORD);
    return (len);
}

void    tokenizer(t_shell *mini, char *input)
{
    int i;
    int count;

    i = 0;
    while (input[i])
    {
        i = handle_space(input, i);
        if (!input[i])
            break;
        if (is_quotes(input[i]))
            count = handle_quoted_token(input, mini, i);
        else if (is_operator(input[i])) 
            count = handle_operator(input, mini, i);
        else
            count = handle_word(input, mini, i);
        i += count;
    }
}