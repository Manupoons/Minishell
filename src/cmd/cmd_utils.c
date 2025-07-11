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

static void	run_cmd(t_shell *mini)
{
	char	*path;
	char	**envp;

	if (!mini->arg || !mini->arg->argv || !mini->arg->argv[0])
		exit(127);
	envp = ft_env_to_array(mini);
	if (mini->arg->fd_in != -1 && mini->arg->fd_in != STDIN_FILENO)
	{
		if (dup2(mini->arg->fd_in, STDIN_FILENO) == -1)
			perror("dup2 fd_in");
		close(mini->arg->fd_in);
		mini->arg->fd_in = -1;
	}
	if (mini->arg->fd_out != -1 && mini->arg->fd_out != STDOUT_FILENO)
	{
		if (dup2(mini->arg->fd_out, STDOUT_FILENO) == -1)
			exit(2);
		close(mini->arg->fd_out);
		mini->arg->fd_out = -1;
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


void close_fds(t_arg *arg)
{
    if (arg->pipe_out != STDOUT_FILENO && arg->pipe_out != -1)
    {
        close(arg->pipe_out);
        arg->pipe_out = -1;
    }
    if (arg->pipe_in != STDIN_FILENO && arg->pipe_in != -1)
    {
        close(arg->pipe_in);
        arg->pipe_in = -1;
    }
}


void child_process(t_shell *mini)
{
	if (!execute_redir_token(mini->arg))
		{
			close_fds(mini->arg);
			exit(1);
		}
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
    t_arg *cmd = mini->arg;
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
