/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:24:06 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/07 17:12:39 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// static int	check_exit_args(t_shell *mini)
// {
// 	int		i;
// 	char	*arg;

// 	i = 0;
// 	arg = mini->arg->argv[1];
// 	if (!arg)
// 		return (0);
// 	if (arg[0] == '-' || arg[0] == '+')
// 		i++;
// 	while (arg[i])
// 	{
// 		if (!ft_isdigit(arg[i]))
// 		{
// 			printf("exit: %s: numeric argument required\n", arg);
// 			return (2);
// 		}
// 		i++;
// 	}
// 	if (mini->arg->argv[2])
// 	{
// 		ft_putendl_fd("exit: too many arguments", 2);
// 		return (1);
// 	}
// 	return (ft_atoi(arg));
// }

// void	ft_exit(t_shell *mini)
// {
// 	ft_putendl_fd("exit", 2);
// 	mini->status = check_exit_args(mini);
// 	if (mini->status != 1)
// 		exit(mini->status);
// }

static long	ft_atol(const char *nptr)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while ('0' <= *nptr && *nptr <= '9')
	{
		num = (num * 10) + (*nptr - '0');
		nptr++;
	}
	return (sign * num);
}

static bool	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_shell *mini)
{
	long	code;

	if (!mini->in_pipe)
		ft_putendl_fd("exit", 2);
	if (mini->arg->argv[1])
	{
		if (!is_numeric(mini->arg->argv[1]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(mini->arg->argv[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(2);
		}
		if (mini->arg->argv[2])
		{
			ft_putendl_fd("exit: too many arguments", 2);
			mini->status = 1;
			return ;
		}
		code = ft_atol(mini->arg->argv[1]);
		exit((unsigned char)code);
	}
	exit((unsigned char)mini->status);
}
