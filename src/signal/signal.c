/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:58:56 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/04 13:00:22 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	g_signal;

static void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal == S_CMD)
	{
		ft_putstr_fd("\n", 1);
		g_signal = S_SIGINT_CMD;
	}
	else if (g_signal == S_HEREDOC)
	{
		ft_putstr_fd("\n", 1);
		g_signal = S_HEREDOC_CANCEL;
	}
	else
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = S_SIGINT;
	}
}

void	init_signal(void)
{
	g_signal = S_BASE;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
