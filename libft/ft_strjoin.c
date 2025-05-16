/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:46:03 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/23 10:09:08 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
