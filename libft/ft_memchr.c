/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:32:45 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/26 10:46:23 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		if (*ptr++ == (unsigned char) c)
			return ((void *)--ptr);
	return (NULL);
}
