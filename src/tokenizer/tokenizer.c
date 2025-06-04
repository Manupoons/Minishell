/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:41:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/06/04 16:12:32 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	handle_space(char *input, int i)
{
	while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n'
		|| input[i] == '\r' || input[i] == '\v' || input[i] == '\f')
		i++;
	return (i);
}

int	handle_quoted_token(char *input, t_token **token_list, int i)
{
	char	*str;
	char	quote;
	int		j;
	int		len;

	quote = input[i]; // esto confirma quote que finalice el loop sean iguales
	j = 1 + i;
	while (input[j] != quote && input[j]) // solo sale si las loops son iguales
		j++;
	if (input[j] == '\0')
		error_message("missing closing quotes.");
	len = j - i - 1;
	str = malloc(len + 1);
	if (!str)
		error_message("failed to alloc mem.");
	ft_strlcpy(str, input + i + 1, len + 1); //revisar funcion returns input
	add_token(str, token_list, TOKEN_WORD);
	return (j - i + 1);
}

int	handle_operator(char *input, t_token **token_list, int i)
{
	if (input[i] == '|')
		return (add_token("|", token_list, TOKEN_PIPE), 1);
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (add_token("<<", token_list, TOKEN_HEREDOC), 2);
		return (add_token("<", token_list, TOKEN_REDIR_IN), 1);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (add_token(">>", token_list, TOKEN_APPEND), 2);
		return (add_token(">", token_list, TOKEN_REDIR_OUT), 1);
	}
	return (0);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

int	handle_word(char *input, t_token **token_list, int i) // for echo
{
	int		start;
	int		len;
	char	*str;

	start = i;
	while (input[i] && !(is_quotes(input[i])) && !(is_operator((input[i])))
		&& (!is_space(input[i])))
		i++;
	len = i - start;
	str = malloc(len + 1);
	if (!str)
		error_message("failed to alloc mem.");
	ft_strlcpy(str, input + start, len + 1);
	add_token(str, token_list, TOKEN_WORD);
	free(str);
	return (len);
}

t_token	*tokenizer(char *input)
{
	t_token	*token_list;
	int		i;
	int		count;

	i = 0;
	token_list = NULL;
	while (input[i])
	{
		i = handle_space(input, i);
		if (!input[i])
		{
			printf("Exiting if enter\n");
			break ;
		}
		if (is_quotes(input[i]))
			count = handle_quoted_token(input, &token_list, i);
		else if (is_operator(input[i]))
			count = handle_operator(input, &token_list, i);
		else
			count = handle_word(input, &token_list, i);
		i += count;
	}
	return (token_list);
}
