/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:21:59 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/20 12:35:11 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	execute_redir(t_shell *msh)
{
	t_redir	*redir;

	redir = msh->arg->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
		{
			if (dup2(redir->fd_in, STDIN_FILENO) == -1)
				perror("dup2 redir out");
			close(redir->fd_in);
			redir->fd_in = -1;
		}
		if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_APPEND)
		{
			if (dup2(redir->fd_out, STDOUT_FILENO) == -1)
				perror("dup2 redir out");
			close(redir->fd_out);
			redir->fd_out = -1;
		}
		redir = redir->next;
	}
}

void	handle_status(t_shell *mini)
{
	if (WIFEXITED(mini->status) && mini->arg && mini->arg->argv && mini->arg->argv[0])
		mini->status = WEXITSTATUS(mini->status);
	if (mini && mini->status == 127)
		printf("%s: %s\n", mini->arg->argv[0], "command not found");
}

void	execute_redir_token(t_arg *args)
{
	t_redir	*redir;

	redir = args->redirs;
	if (!redir)
		return ;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
			redir->fd_in = open(redir->cmd, O_RDONLY);
		if (redir->type == TOKEN_REDIR_OUT)
		{
			redir->fd_out = open(redir->cmd, O_WRONLY | O_CREAT
					| O_TRUNC, 0777);
			if (redir->fd_out == -1)
				perror("open redir out failed");
		}
		if (redir->type == TOKEN_APPEND)
			redir->fd_out = open(redir->cmd, O_WRONLY | O_CREAT
					| O_APPEND, 0777);
		if (redir->type == TOKEN_HEREDOC)
			redir->fd_in = open(redir->cmd, O_RDONLY);
		redir = redir->next;
	}
}
