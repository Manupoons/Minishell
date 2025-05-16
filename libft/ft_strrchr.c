/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:15:52 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/20 13:32:41 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			ptr = (char *)&s[i];
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (ptr);
}
