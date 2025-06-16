/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:33:04 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/07 10:15:55 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	run_cmd(t_shell *mini)
{
	char	*path;
	char	**envp;

	if (!mini->arg || !mini->arg->argv || !mini->arg->argv[0])
		exit(127);
	envp = ft_env_to_array(mini);
	if (mini->arg->redirs)
	{
		if (mini->arg->redirs->fd_in != 0)
			dup2(mini->arg->redirs->fd_in, STDIN_FILENO);
		if (mini->arg->redirs->fd_out != 1)
			dup2(mini->arg->redirs->fd_out, STDOUT_FILENO);
	}
	path = ft_get_path(mini->arg->argv[0], mini->env);
	if (!mini->arg->argv || !mini->arg->argv[0]
		|| !ft_isalnum(mini->arg->argv[0][0]))
	{
		ft_memfree(path);
		path = mini->arg->argv[0];
	}
	execve(path, mini->arg->argv, envp);
	exit(127);
}

bool	has_stdout_redirection(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_APPEND)
			return (true);
		redir = redir->next;
	}
	return (false);
}

void	child_process(t_shell *msh)
{
	if (msh->arg->pipe_in != STDIN_FILENO)
	{
		dup2(msh->arg->pipe_in, STDIN_FILENO);
		close(msh->arg->pipe_in);
	}
	if ((msh->arg->pipe_out != STDOUT_FILENO)
		&& !has_stdout_redirection(msh->arg->redirs))
	{
		dup2(msh->arg->pipe_out, STDOUT_FILENO);
		close(msh->arg->pipe_out);
	}
	execute_redir(msh);
	if (is_comms(msh))
		ft_comms(msh);
	else
		run_cmd(msh);
	exit(127);
}
