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

static char	*extract_quoted_fragment(char *input, int *i)
{
	char	quote;
	int		start;
	int		end;
	int		len;

	quote = input[*i];
	start = *i + 1;
	end = start;
	while (input[end] && input[end] != quote)
		end++;
	if (!input[end])
		return (printf("missing closing quotes.\n"), NULL);
	len = end - start;
	*i = end + 1;
	return (ft_substr(input, start, len));
}

static char	*extract_unquoted_fragment(char *input, int *i)
{
	int		start;
	int		end;
	int		len;

	start = *i;
	end = start;
	while (input[end] && !is_space(input[end]) && !is_operator(input[end])
		&& !is_quotes(input[end]))
		end++;
	len = end - start;
	*i = end;
	return (ft_substr(input, start, len));
}

int	handle_compound_words(char *input, t_token **token_list, int i)
{
	char	quote;
	char	*frag;
	char	*word;
	int		start;

	start = i;
	word = ft_strdup("");
	if (!word)
		return (-1);
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
	{
		quote = is_quotes(input[i]);
		if (quote != 0)
			frag = extract_quoted_fragment(input, &i);
		else
			frag = extract_unquoted_fragment(input, &i);
		if (!frag)
			return (free(word), -1);
		word = ft_join_free(word, frag);
		if (!word)
			return (-1);
	}
	add_token(word, token_list, TOKEN_WORD, 0);
	free(word);
	return (i - start);
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
			break ;
		if (is_operator(input[i]))
			count = handle_operator(input, &token_list, i);
		else
			count = handle_compound_words(input, &token_list, i);
		if (count == -1)
		{
			if (token_list)
				free_tokens(token_list);
			return (NULL);
		}
		i += count;
	}
	return (token_list);
}
