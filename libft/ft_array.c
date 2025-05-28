/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:53:16 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/28 17:54:02 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arrayadd(char *str, char **array)
{
	char	**new_array;
	int		i;

	if (!array)
	{
		array = ft_calloc(sizeof(char *), 2);
		array[0] = str;
		return (array);
	}
	else
	{
		new_array = ft_calloc(sizeof(char *), ft_arraylen(array) + 2);
		i = -1;
		while (array[++i])
			new_array[i] = ft_strdup(array[i]);
		new_array[i] = ft_strdup(str);
		ft_memfree_all(array);
		free(str);
		return (new_array);
	}
}

char	**ft_arraydup(char **array)
{
	char	**new_array;
	int		i;

	if (!array)
		return (NULL);
	new_array = ft_calloc(sizeof(char *), ft_arraylen(array) + 1);
	i = 0;
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	return (new_array);
}

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}
