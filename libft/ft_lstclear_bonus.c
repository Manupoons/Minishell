/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:59:46 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/25 13:25:11 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	if (*lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		temp = current -> next;
		del(current->content);
		free(current);
		current = temp;
	}
	*lst = NULL;
}
