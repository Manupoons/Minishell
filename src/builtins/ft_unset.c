/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:09:06 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/04 16:02:44 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_unset(t_shell *mini)
{
	int		i;
	char	*name;
	t_env	*curr;
	t_env	*prev;

	i = 0;
	while (mini->arg->argv[++i])
	{
		name = mini->arg->argv[i];
		if (!check_export(name))
		{
			mini->status = 1;
			continue ;
		}
		curr = mini->env;
		prev = NULL;
		while (curr)
		{
			if (ft_strcmp(curr->env_name, name) == 0)
			{
				if (prev)
					prev->next = curr->next;
				else
					mini->env = curr->next;
				ft_memfree(curr->env_name);
				ft_memfree(curr->env_value);
				free(curr);
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
	}
}
