/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:41:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/06/10 17:02:53 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	handle_quoted_token(char *input, t_token **token_list, int i, char quote)
{
	char	*str;
	int		j;
	int		len;

	j = 1 + i;
	while (input[j] != quote && input[j])
		j++;
	if (input[j] == '\0')
		error_message("missing closing quotes.");
	len = j - i - 1;
	str = malloc(len + 1);
	if (!str)
		error_message("failed to alloc mem.");
	ft_strlcpy(str, input + i + 1, len + 1);
	add_token(str, token_list, TOKEN_WORD, quote);
	free(str);
	return (j - i + 1);
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

int	handle_word(char *input, t_token **token_list, int i)
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
	add_token(str, token_list, TOKEN_WORD, 0);
	free(str);
	return (len);
}

t_token	*tokenizer(char *input)
{
	t_token	*token_list;
	int		i;
	int		count;
	char	quote;

	i = 0;
	token_list = NULL;
	while (input[i])
	{
		i = handle_space(input, i);
		if (!input[i])
			break ;
		quote = is_quotes(input[i]);
		if (quote != 0)
			count = handle_quoted_token(input, &token_list, i, quote);
		else if (is_operator(input[i]))
			count = handle_operator(input, &token_list, i);
		else
			count = handle_word(input, &token_list, i);
		i += count;
	}
	return (token_list);
}
