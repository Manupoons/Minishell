/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:35:40 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/26 10:17:34 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	alloc_size;
	size_t	start1;

	i = 0;
	start1 = (size_t) start;
	if (!s)
		return (NULL);
	if (start1 > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start1)
		alloc_size = ft_strlen(s) - start1;
	else
		alloc_size = len;
	ptr = malloc(alloc_size + 1);
	if (ptr == NULL)
		return (0);
	while (i < len && s[start1 + i])
	{
		ptr[i] = (char )s[start1 + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
