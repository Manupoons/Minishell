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


void child_process(t_shell *mini)
{
	t_arg *arg = mini->arg;

	if (arg->pipe_in != STDIN_FILENO)
	{
		if (dup2(arg->pipe_in, STDIN_FILENO) == -1)
		{
			perror("dup2 pipe_in failed");
			exit(1);
		}
	}
	if (!has_stdout_redirection(arg->redirs) && arg->pipe_out != STDOUT_FILENO)
	{
		if (dup2(arg->pipe_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe_out failed");
		}
	}
	execute_redir(mini);
	if (is_comms(mini))
	{
		ft_comms(mini);
		exit(0);
	}
	else
	{
		run_cmd(mini);
		exit(127);
	}
}
