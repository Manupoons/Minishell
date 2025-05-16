/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:55:10 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/24 16:02:25 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] && little[j]
			&& (i + j) < len && little[j] == big[i + j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
