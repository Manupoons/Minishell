/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:41:35 by jdorazio          #+#    #+#             */
/*   Updated: 2025/06/06 17:11:47 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*handle_quoted_token(char *input, int *i, char quote)
{
	char	*str;
	int		j;
	int		len;

	j = 1 + (*i);
	while (input[j] != quote && input[j])
		j++;
	if (input[j] == '\0')
		error_message("missing closing quotes.");
	len = j - (*i) - 1;
	str = malloc(len + 1);
	if (!str)
		error_message("failed to alloc mem.");
	ft_strlcpy(str, input + (*i) + 1, len + 1);
	(*i) = j + 1;
	//add_token(str, token_list, TOKEN_WORD, quote);
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

char *handle_word(char *input, int *i)
{
	int		start;
	int		len;
	char	*str;

	start = (*i);
	while (input[(*i)] && !(is_quotes(input[(*i)])) && !(is_operator((input[(*i)])))
		&& (!is_space(input[(*i)])))
		(*i)++;
	len = (*i) - start;
	str = malloc(len + 1);
	if (!str)
		error_message("failed to alloc mem.");
	ft_strlcpy(str, input + start, len + 1);
	//add_token(str, token_list, TOKEN_WORD, 0);
	return (str);
}

char	ft_strjoin_free(char *dst, char *src)
{
	char	*joined;

	temp = ft_strjoin(dst, src);
	free(src);
	free(dst);
	return(temp);
}

int	handle_compound_words(char *input, t_token **token_list, int i)
{
	char	quote;
	char	*cw;
	int		start;
	int		quote_flag;

	start = i;
	quote_flag = 0;
	cw = ft_strdup("");
	while (input[i]  && !is_space(input[i]) && !is_operator(input[i]))
	{
		quote = is_quotes(input[i]);
		if (quote != 0)
			cw = ft_strjoin(cw, handle_quoted_token(input, &i, quote));
		else
			cw = ft_strjoin(cw, handle_word(input, &i));
	}
	add_token(cw, token_list, TOKEN_WORD, quote);
	free(cw);
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
		i += count;
	}
	return (token_list);
}
