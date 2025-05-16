/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:37:41 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/25 10:52:19 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	i;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && check(set, s1[start]) != 0)
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && check(set, s1[end]) != 0)
		end--;
	ptr = malloc(end - start + 2);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < end - start + 1)
	{
		ptr[i] = s1[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
