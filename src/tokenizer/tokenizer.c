/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:41:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/11 08:04:11 by jdorazio         ###   ########.fr       */
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

int	handle_compound_words(char *input, t_token **token_list, int i)
{
	char	*fragment;
	int		start;
	char	quote;

	start = i;
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
	{
		quote = is_quotes(input[i]);
		if (quote)
			fragment = handle_quoted_token(input, &i, quote);
		else
			fragment = handle_word(input, &i);
		if (!fragment)
			return (-1);
		add_token(fragment, token_list, TOKEN_WORD, quote);
		free(fragment);
	}
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
