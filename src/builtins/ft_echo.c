/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:50 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/28 16:19:42 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

void	ft_echo(t_shell *mini)
{
	int i;

	i = 1;
	mini->status = 0;
	if (mini->arg->argv[i] && !ft_strncmp(mini->arg->argv[i], "-n", 2))
		i++;
 	while (mini->arg->argv[i])
	{
		ft_putstr_fd(mini->arg->argv[i++], mini->parser->fd_out);
		if (mini->arg->argv[i])
			ft_putchar_fd(32, mini->parser->fd_out);
	}
	if (!(mini->arg->argv[i] && !ft_strncmp(mini->arg->argv[i], "-n", 2)))
		ft_putchar_fd(10, mini->parser->fd_out);
}
