/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:24:06 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/20 10:58:11 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	check_exit_args(t_shell *mini)
{
	int		i;
	char	*arg;

	i = 0;
	arg = mini->arg->argv[1];
	if (!arg)
		return (0);
	if (arg[0] == '-' || arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			printf("exit: %s: numeric argument required\n", arg);
			return (2);
		}
		i++;
	}
	if (mini->arg->argv[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	return (ft_atoi(arg));
}

void	ft_exit(t_shell *mini)
{
	ft_putendl_fd("exit", 2);
	mini->status = check_exit_args(mini);
	if (mini->status != 1)
		exit(mini->status);
}
