/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:21:59 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/11 08:24:40 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// void	execute_redir(t_arg *arg)
// {
// 	if (!arg)
// 		return ;
// 	if (arg->fd_out != -1)
// 	{
// 		if (dup2(arg->fd_out, STDOUT_FILENO) == -1)
// 		{
// 			exit(2);
// 		}
// 		close(arg->fd_out);
// 		arg->fd_out = -1;
// 	}
// 	if (arg->fd_in != -1)
// 	{
// 		if (dup2(arg->fd_in, STDIN_FILENO) == -1)
// 		{
// 			exit(2);
// 		}
// 		close(arg->fd_in);
// 		arg->fd_in = -1;
// 	}
// }

int execute_redir(t_arg *arg)
{
    t_redir *redir = arg->redirs;
    while (redir)
    {
        if (redir->type == TOKEN_REDIR_IN && !open_infile(arg, redir))
					return (0);
        else if (redir->type == TOKEN_REDIR_OUT && !open_outfile(arg, redir))
					return (0);
				else if (redir->type == TOKEN_APPEND && open_append(arg, redir))
					return (0);
				else if (redir->type == TOKEN_HEREDOC)
				{
					if (!handle_heredoc(arg, redir)
						|| dup2(arg->fd_in, STDIN_FILENO) == -1)
						return (0);
				}
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
	if (mini->status == 127 && g_signal == S_BASE
		&& mini->arg && mini->arg->argv && mini->arg->argv[0])
		printf("%s: command not found\n", mini->arg->argv[0]);
}

// int	execute_redir_token(t_arg *args)
// {
// 	if (!args || !args->redirs)
// 		return (1);
// 	if (args->redirs->type == TOKEN_REDIR_IN)
// 	{
// 		if (!open_infile(args, args->redirs))
// 			return (0);
// 	}
// 	else if (args->redirs->type == TOKEN_REDIR_OUT)
// 	{
// 		if (!open_outfile(args, args->redirs))
// 			return (0);
// 	}
// 	else if (args->redirs->type == TOKEN_APPEND)
// 	{
// 		if (!open_append(args, args->redirs))
// 			return (0);
// 	}
// 	else if (args->redirs->type == TOKEN_HEREDOC)
// 	{
// 		if (!handle_heredoc(args, args->redirs))
// 			return (0);
// 	}
// 	return (execute_redir_token(args->next));
// }

// int	execute_redir_token(t_arg *args)
// {
// 	t_redir	*redir;

// 	redir = args->redirs;
// 	while (redir)
// 	{
// 		if (redir->type == TOKEN_REDIR_IN)
// 		{
// 			if (!open_infile(args, redir))
// 				return (0);
// 		}
// 		else if (redir->type == TOKEN_REDIR_OUT)
// 		{
// 			if (!open_outfile(args, redir))
// 				return (0);
// 		}
// 		else if (redir->type == TOKEN_APPEND)
// 		{
// 			if (!open_append(args, redir))
// 				return (0);
// 		}
// 		else if (redir->type == TOKEN_HEREDOC)
// 		{
// 			if (!handle_heredoc(args, redir))
// 				return (0);
// 		}
// 		redir = redir->next;
// 	}
// 	return (1);
// }
