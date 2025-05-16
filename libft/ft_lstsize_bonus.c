/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:48:55 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/25 10:30:08 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;
	t_list	*current;

	current = lst;
	i = 0;
	if (!lst)
		return (0);
	while (current != NULL)
	{
		current = current -> next;
		i++;
	}
	return (i);
}
