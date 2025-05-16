/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:42:06 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/25 10:52:53 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_content;

	new_content = (t_list *) malloc(sizeof(t_list));
	if (!new_content)
		return (NULL);
	new_content -> content = content;
	new_content -> next = NULL;
	return (new_content);
}
