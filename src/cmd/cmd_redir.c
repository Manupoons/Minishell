/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:21:59 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/12 18:42:36 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	process_heredoc(t_arg *arg)
{
	t_redir	*redir;

	redir = arg->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			if (!handle_heredoc(arg, redir))
				return ;
		}
		redir = redir->next;
	}
}

int	execute_redir(t_arg *arg)
{
	t_redir	*redir;

	redir = arg->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN && !open_infile(arg, redir))
			return (0);
		else if (redir->type == TOKEN_HEREDOC)
		{
			if (dup2(arg->fd_in, STDIN_FILENO) == -1)
				return (0);
		}
		else if (redir->type == TOKEN_REDIR_OUT && !open_outfile(arg, redir))
			return (0);
		else if (redir->type == TOKEN_APPEND && !open_append(arg, redir))
			return (0);
		redir = redir->next;
	}
	return (1);
}

void	handle_status(t_shell *mini)
{
	int	status;

	if (WIFSIGNALED(mini->status))
	{
		status = WTERMSIG(mini->status);
		if (status == SIGINT)
		{
			g_signal = S_SIGINT_CMD;
			mini->status = 128 + SIGINT;
		}
		else if (status == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			mini->status = 128 + SIGQUIT;
		}
	}
	else if (WIFEXITED(mini->status))
	{
		mini->status = WEXITSTATUS(mini->status);
		g_signal = S_BASE;
	}
}
