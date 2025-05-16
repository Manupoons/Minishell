/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:23:32 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/19 16:04:31 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	ptr1 = (unsigned char *) dest;
	ptr2 = (unsigned char *) src;
	if (n == 0 || ptr1 == ptr2)
		return (dest);
	else if (ptr1 > ptr2)
	{
		i = n;
		while (i > 0)
		{
			ptr1[i -1] = ptr2[i -1];
			i--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
