/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:50 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/29 18:01:05 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_echo(t_shell *mini)
{
	int	i;

	i = 1;
	mini->status = 0;
	if (mini->arg->argv[i] && !ft_strncmp(mini->arg->argv[i], "-n", 2))
		i++;
	while (mini->arg->argv[i])
	{
		ft_putstr_fd(mini->arg->argv[i++], mini->parser->fd_out);
		if (mini->arg->argv[i])
			ft_putchar_fd(' ', mini->parser->fd_out);
	}
	if (!(mini->arg->argv[1] && !ft_strncmp(mini->arg->argv[1], "-n", 2)))
		ft_putchar_fd('\n', mini->parser->fd_out);
}
