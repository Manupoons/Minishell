/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:33:42 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/20 15:47:56 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
