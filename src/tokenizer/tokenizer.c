/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:41:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/12 13:09:55 by jdorazio         ###   ########.fr       */
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

static int	is_valid_var_assign(const char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] != '=')
		return (0);
	if (str[i + 1] == '\0')
		return (0);
	return (1);
}

int	handle_compound_words(char *input, t_token **token_list, int i)
{
	int		start;
	char	quote;
	char	*fragment;
	char	*full_token;

	start = i;
	full_token = ft_strdup("");
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
	{
		quote = is_quotes(input[i]);
		if (quote)
			fragment = handle_quoted_token(input, &i, quote);
		else
			fragment = handle_word(input, &i);
		if (!fragment)
			return (free(full_token), -1);
		full_token = ft_join_free(full_token, fragment);
	}
	if (is_valid_var_assign(full_token))
		add_token(full_token, token_list, TOKEN_WORD, quote);
	else
		add_token(full_token, token_list, TOKEN_WORD, 0);
	free(full_token);
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
