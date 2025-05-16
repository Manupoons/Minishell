/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:39:35 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/28 15:03:52 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// funcion que cuenta la cantidad de filas basandose en los separadores
static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;
	size_t	words;

	i = 0;
	count = 0;
	words = 0;
	while (s[i])
	{
		if (c == s[i])
			words = 0;
		else
		{
			if (!words)
			{
				count++;
				words = 1;
			}
		}
		i++;
	}
	return (count);
}

static size_t	ft_get_word_length(char const *s, char c)
{
	size_t	i;
	size_t	word_length;

	word_length = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		word_length++;
		i++;
	}
	return (word_length);
}

static void	ft_free_alloc_memory(char **ptr, size_t i)
{
	while (i > 0)
		free(ptr[--i]);
	free(ptr);
}

static char	*ft_splitter(const char **s, char c)
{
	size_t	word_len;
	size_t	j;
	char	*word;

	word_len = ft_get_word_length(*s, c);
	word = ft_calloc(word_len + 1, sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (**s && **s == c)
		(*s)++;
	while (**s && **s != c)
	{
		word[j++] = **s;
		(*s)++;
	}
	word[j] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	word_count;

	i = 0;
	word_count = ft_count_words(s, c);
	ptr = ft_calloc(word_count + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	while (i < word_count)
	{
		ptr[i] = ft_splitter(&s, c);
		if (!ptr[i])
		{
			ft_free_alloc_memory(ptr, i);
			return (NULL);
		}
		i++;
	}
	return (ptr);
}
