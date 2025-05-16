/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:40:57 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/12 16:17:25 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		len;

	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = 0;
	if (size == 0)
		dst = NULL;
	else
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	if (size > 0)
		dst[i] = '\0';
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	str_len1;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	str_len1 = ft_strlen(s1);
	ptr = malloc(str_len1 + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < str_len1)
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		ptr[str_len1 + i] = s2[i];
		i++;
	}
	ptr[str_len1 + i] = '\0';
	return (ptr);
}

char	*ft_strchr(const char	*s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char) c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
