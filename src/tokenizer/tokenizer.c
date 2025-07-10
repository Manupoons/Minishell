/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:41:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/06/25 19:20:46 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*handle_quoted_token(char *input, int *i, char quote)
{
	char	*str;
	int		end;
	int		start;
	int		len;

	start = (*i);
	end = 1 + start;
	while (input[end] != quote && input[end])
		end++;
	if (!input[end])
		return (printf("missing closing quotes.\n"), NULL);
	len = end - start - 1;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, input + start + 1, len + 1);
	(*i) = end + 1;
	return (str);
}

int	handle_operator(char *input, t_token **token_list, int i)
{
	if (input[i] == '|')
		return (add_token("|", token_list, TOKEN_PIPE, 0), 1);
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			return (add_token("<<", token_list, TOKEN_HEREDOC, 0), 2);
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

char	*handle_word(char *input, int *i)
{
	int		start;
	int		len;
	char	*str;

	start = (*i);
	while (input[(*i)] && !(is_quotes(input[(*i)]))
		&& !(is_operator((input[(*i)]))) && (!is_space(input[(*i)])))
		(*i)++;
	len = (*i) - start;
	str = malloc(len + 1);
	if (!str)
		printf("failed to alloc mem.");
	ft_strlcpy(str, input + start, len + 1);
	return (str);
}

int	handle_compound_words(char *input, t_token **token_list, int i)
{
	char	quote;
	char	*cw;
	int		start;

	start = i;
	cw = ft_strdup("");
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
	{
		quote = is_quotes(input[i]);
		if (quote != 0)
		{
			cw = ft_join_free(cw, handle_quoted_token(input, &i, quote));
			if (!cw)
				return (free(cw), -1);
		}
		else
			cw = ft_join_free(cw, handle_word(input, &i));
	}
	add_token(cw, token_list, TOKEN_WORD, quote);
	free(cw);
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
			*status = 2;
			return (NULL);
		}
		i += count;
	}
	return (token_list);
}