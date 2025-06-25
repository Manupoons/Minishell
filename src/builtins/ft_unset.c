/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:09:06 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/07 10:20:27 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	unset_util(t_shell *mini, t_env *prev, t_env *curr)
{
	if (prev)
		prev->next = curr->next;
	else
		mini->env = curr->next;
	ft_memfree(curr->env_name);
	ft_memfree(curr->env_value);
	free(curr);
}

void	ft_unset(t_shell *mini)
{
	int		i;
	t_env	*curr;
	t_env	*prev;

	i = 0;
	while (mini->arg->argv[++i])
	{
		if (!check_export(mini->arg->argv[++i]))
		{
			mini->status = 1;
			continue ;
		}
		curr = mini->env;
		prev = NULL;
		while (curr)
		{
			if (ft_strcmp(curr->env_name, mini->arg->argv[i]) == 0)
			{
				unset_util(mini, prev, curr);
				break ;
			}
			prev = curr;
			curr = curr->next;
		}
	}
}
