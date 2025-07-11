/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 08:02:10 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/11 08:04:45 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*extract_single_quotes(char *input, int *i)
{
	int		start;
	char	*res;

	start = (*i) + 1;
	(*i)++;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (!input[*i])
		return (printf("missing closing single quote\n"), NULL);
	res = ft_substr(input, start, *i - start);
	(*i)++;
	return (res);
}

char	*extract_double_quotes(char *input, int *i)
{
	int		start;
	int		end;
	char	*buf;
	int		j;

	start = (*i) + 1;
	end = start;
	j = 0;
	buf = malloc(ft_strlen(input) + 1);
	if (!buf)
		return (NULL);
	while (input[end] && input[end] != '"')
	{
		if (input[end] == '\\' && (input[end + 1] == '"'
				|| input[end + 1] == '\\' || input[end + 1] == '$'))
			buf[j++] = input[++end];
		else
			buf[j++] = input[end];
		end++;
	}
	if (!input[end])
		return (free(buf), printf("missing closing double quote\n"), NULL);
	buf[j] = '\0';
	*i = end + 1;
	return (buf);
}

char	*handle_quoted_token(char *input, int *i, char quote)
{
	if (quote == '"')
		return (extract_double_quotes(input, i));
	else
		return (extract_single_quotes(input, i));
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
