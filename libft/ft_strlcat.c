/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:08:21 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/19 18:10:06 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0 || size <= dst_len)
		return (size + src_len);
	i = 0;
	while ((i < size - dst_len - 1) && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if (size > 0)
		dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
