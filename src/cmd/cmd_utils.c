/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:33:04 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/11 08:37:39 by jdorazio         ###   ########.fr       */
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

static void	prepare_fds(t_arg *arg)
{
	if (arg->fd_in != -1 && arg->fd_in != STDIN_FILENO)
	{
		if (dup2(arg->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 fd_in");
			exit(2);
		}
		close(arg->fd_in);
		arg->fd_in = -1;
	}
	if (arg->fd_out != -1 && arg->fd_out != STDOUT_FILENO)
	{
		if (dup2(arg->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 fd_in");
			exit(2);
		}
		close(arg->fd_out);
		arg->fd_out = -1;
	}
}

static void	run_cmd(t_shell *mini)
{
	char	*path;
	char	**envp;

	if (!mini->arg || !mini->arg->argv || !mini->arg->argv[0])
		exit(127);
	envp = ft_env_to_array(mini);
	prepare_fds(mini->arg);
	if (ft_strchr(mini->arg->argv[0], '/'))
		path = ft_strdup(mini->arg->argv[0]);
	else
		path = ft_get_path(mini->arg->argv[0], mini->env);
	if (!path)
		exit(127);
	run_cmd_error(mini, path, envp);
}

static void	setup_redir_and_pipes(t_shell *mini)
{
	if (!execute_redir_token(mini->arg))
			exit(1);
	execute_redir(mini);
  if (mini->arg->pipe_in != STDIN_FILENO)
  {
    dup2(mini->arg->pipe_in, STDIN_FILENO);
    close(mini->arg->pipe_in);
  }
  if (mini->arg->pipe_out != STDOUT_FILENO)
  {
		dup2(mini->arg->pipe_out, STDOUT_FILENO);
    close(mini->arg->pipe_out);
  }
}

void child_process(t_shell *mini)
{
	t_arg *cmd;

	setup_redir_and_pipes(mini);
	cmd = mini->arg;
	if (cmd->pipe_in != STDIN_FILENO)
  {
    dup2(cmd->pipe_in, STDIN_FILENO);
		close(cmd->pipe_in);
  }
  if (cmd->pipe_out != STDOUT_FILENO)
  {
    dup2(cmd->pipe_out, STDOUT_FILENO);
    close(cmd->pipe_out);
  }
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
