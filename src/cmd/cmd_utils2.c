/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:33:04 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/06 11:09:22 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	run_cmd_error(t_shell *mini, char *path, char **envp)
{
	if (access(path, X_OK) == -1)
	{
		perror(mini->arg->argv[0]);
		if (errno == EACCES)
			exit(126);
		else
			exit(127);
	}
	execve(path, mini->arg->argv, envp);
	perror(mini->arg->argv[0]);
	if (errno == EACCES)
		exit(126);
	else
		exit(127);
}

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
		{
			dup2(mini->arg->redirs->fd_in, STDIN_FILENO);
			close(mini->arg->redirs->fd_in);
		}
		if (mini->arg->redirs->fd_out != 1)
		{
			dup2(mini->arg->redirs->fd_out, STDOUT_FILENO);
			close(mini->arg->redirs->fd_out);
		}
	}
	if (ft_strchr(mini->arg->argv[0], '/'))
		path = ft_strdup(mini->arg->argv[0]);
	else
		path = ft_get_path(mini->arg->argv[0], mini->env);
	if (!path)
		exit(127);
	run_cmd_error(mini, path, envp);
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
	execute_redir(msh);
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
	if (is_comms(msh))
	{
		ft_comms(msh);
		exit(0);
	}
	else
		run_cmd(msh);
	exit(127);
}
