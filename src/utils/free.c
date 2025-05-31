/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:16:16 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/31 12:10:06 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_free_env(t_env **env)
{
	t_env	*temp;

	while (*env)
	{
		temp = (*env)->next;
		ft_memfree((*env)->env_name);
		ft_memfree((*env)->env_value);
		ft_memfree((*env));
		*env = temp;
	}
	*env = NULL;
}

void	ft_free_list(t_env **env)
{
	t_env	*temp;

	while (*env)
	{
		temp = (*env)->next;
		ft_memfree((*env)->env_name);
		ft_memfree((*env)->env_value);
		ft_memfree((*env));
		*env = temp;
	}
	*env = NULL;
}
