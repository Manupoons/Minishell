/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:24:06 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/29 16:28:11 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	check_exit_args(t_shell *mini)
{
	int	i;

	i = 0;
	if (!mini->arg->argv[i])
		return (1);
	if (mini->arg->argv[1])
	{
		while (mini->arg->argv[++i])
		{
			if (!ft_isdigit(mini->arg->argv[1][i]))
			{
				printf("exit: %s: numeric argument required\n",
					mini->arg->argv[i]);
				return (2);
			}
		}
		return (ft_atoi(mini->arg->argv[i]));
	}
	return (0);
}

void	ft_exit(t_shell *mini)
{
	ft_putendl_fd("exit", 2);
	mini->status = check_exit_args(mini);
	if (mini->status != 1)
		exit(mini->status);
	ft_putendl_fd("exit: too many arguments", 2);
}
