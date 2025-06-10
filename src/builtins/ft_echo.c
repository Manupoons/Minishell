/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:50 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/06 17:04:54 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	n_flag(char *str, int *flag)
{
	int	i;

	if (!str || str[0]  != '-')
		return (*flag);
	i = 1;
	if (str[i] == '\0')
		return (*flag);
	while (str[i])
	{
		if (str[i] != 'n')
			return (*flag);
		i++;
	}
	*flag = 1;
	return (1);
}

void	ft_echo(t_shell *mini)
{
	int		i;
	char	*arg;
	int		flag;

	mini->status = 0;
	i = 1;
	flag = 0;
	if (mini->arg->argv[i] && n_flag(mini->arg->argv[i], &flag))
		i++;
	while (mini->arg->argv[i])
	{
		arg = mini->arg->argv[i];
		ft_putstr_fd(arg, STDOUT_FILENO);
		if (mini->arg->argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!(flag))
		ft_putchar_fd('\n', STDOUT_FILENO);
}
