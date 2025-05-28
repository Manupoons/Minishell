/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memfree_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:45:22 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/28 15:46:25 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memfree_all(char **ptr)
{
	int	i;

	if (!ptr)
		return;
	i = 0;
	while (ptr[i])
		ft_memfree(ptr[i++]);
	free(ptr);
	ptr = NULL;
}