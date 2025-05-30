/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:37:51 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/29 16:08:08 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	ft_found_quotes(char *line, int *i)
{
	char	quote;

	quote = 0;
	if ((line[*i] == '"' || line[*i] == '\'') && line[*i])
	{
		quote = line[*i];
		*i = *i + 1;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i] == quote)
			(*i)++;
		return (1);
	}
	return (0);
}

static int	ft_found_word(char *line, char s, int *i)
{
	if (line[*i] != s && line[*i])
	{
		while (line[*i] && line[*i] != s)
		{
			ft_found_quotes(line, i);
			*i = *i + 1;
		}
		return (1);
	}
	return (0);
}

static int	ft_count_words(char *line, char s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] == s && line[i])
			i++;
		if (line[i])
			count += ft_found_word(line, s, &i);
		if (line[i])
			ft_found_quotes(line, &i);
	}
	return (count);
}

static char	*split_token(char *line, int *i, char s, int *start)
{
	char	quote;

	while (line[*i] == s)
		(*i)++;
	*start = *i;
	if (line[*i] == '"' || line[*i] == '\'')
	{
		quote = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != quote)
			(*i)++;
		if (line[*i])
			(*i)++;
	}
	else
	{
		while (line[*i] && line[*i] != s && line[*i] != '"' && line[*i] != '\'')
			(*i)++;
	}
	return (ft_substr(line, *start, *i - *start));
}

char	**shell_split(t_shell *mini, char *line, char s)
{
	char	**split;
	char	*temp;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	split = ft_calloc(ft_count_words(line, s) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	while (line[i])
	{
		if (line[i] != s)
		{
			temp = split_token(line, &i, s, &start);
			split[j++] = ft_strtrim(temp, "\"\'");
			ft_memfree(temp);
		}
		else
			i++;
	}
	split[j] = NULL;
	mini->arg->args_count = j;
	return (split);
}
