/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:41:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/07 17:37:33 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	handle_operator(char *input, t_token **token_list, int i)
{
	if (input[i] == '|')
		return (add_token("|", token_list, TOKEN_PIPE, 0), 1);
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (add_token("<<", token_list, TOKEN_HEREDOC, 0), 2);
		// else if (input[i + 1] == '>')
		// 	return (add_token("<>", token_list, TOKEN_REDIR_INOUT, 0), 1);
		return (add_token("<", token_list, TOKEN_REDIR_IN, 0), 1);
	}
	else if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			return (add_token(">>", token_list, TOKEN_APPEND, 0), 2);
		return (add_token(">", token_list, TOKEN_REDIR_OUT, 0), 1);
	}
	return (0);
}

// char	*handle_word(char *input, int *i)
// {
// 	int		start;
// 	int		len;
// 	char	*str;

// 	start = (*i);
// 	while (input[(*i)] && !(is_quotes(input[(*i)]))
// 		&& !(is_operator((input[(*i)]))) && (!is_space(input[(*i)])))
// 		(*i)++;
// 	len = (*i) - start;
// 	str = malloc(len + 1);
// 	if (!str)
// 		printf("failed to alloc mem.");
// 	ft_strlcpy(str, input + start, len + 1);
// 	return (str);
// }

static char	*extract_quoted_fragment(char *input, int *i, int *quote_type)
{
	char	quote;
	int		j;
	char	*buffer;

	quote = input[*i];
	*quote_type = quote; // Guardamos tipo de quote
	buffer = malloc(ft_strlen(input) + 1);
	if (!buffer)
		return (NULL);
	j = 0;
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		if (input[*i] == '\\' && input[*i + 1])
			(*i)++;
		buffer[j++] = input[*i];
		(*i)++;
	}
	if (input[*i] != quote)
		return (printf("missing closing quotes.\n"), free(buffer), NULL);
	(*i)++;
	buffer[j] = '\0';
	return (buffer);
}


static char	*extract_unquoted_fragment(char *input, int *i)
{
	char	*buffer;
	int		j;

	buffer = malloc(ft_strlen(input) + 1);
	if (!buffer)
		return (NULL);
	j = 0;
	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]))
	{
		if (input[*i] == '\\' && input[*i + 1])
		{
			(*i)++;
			buffer[j++] = input[*i];
		}
		else
			buffer[j++] = input[*i];
		(*i)++;
	}
	buffer[j] = '\0';
	return (buffer);
}
int	handle_compound_words(char *input, t_token **token_list, int i)
{
	char	*frag;
	char	*word;
	int		start;
	int		quote_type = 0;

	start = i;
	word = ft_strdup("");
	if (!word)
		return (-1);
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
	{
		int local_quote = 0;
		if (is_quotes(input[i]))
			frag = extract_quoted_fragment(input, &i, &local_quote);
		else
			frag = extract_unquoted_fragment(input, &i);
		if (!frag)
			return (free(word), -1);
		word = ft_join_free(word, frag);
		if (quote_type == 0) // usamos el primer quote si existe
			quote_type = local_quote;
	}
	add_token(word, token_list, TOKEN_WORD, quote_type); // Guardamos el tipo de quote
	free(word);
	return (i - start);
}

t_token	*tokenizer(char *input, int *status)
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
			break ;
		if (is_operator(input[i]))
			count = handle_operator(input, &token_list, i);
		else
			count = handle_compound_words(input, &token_list, i);
		if (count == -1)
		{
			if (token_list)
				free_tokens(token_list);
			return (*status = 2, NULL);
		}
		i += count;
	}
	return (token_list);
}
