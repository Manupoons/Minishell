/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:14:03 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/04 19:26:11 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	run_cmd(t_shell *mini)
{
	char	*path;
	char	**envp;

	envp = ft_env_to_array(mini);
	if (mini->arg->redirs)
	{
		if (mini->arg->redirs->fd_in != 0)
			dup2(mini->arg->redirs->fd_in, STDIN_FILENO);
		if (mini->arg->redirs->fd_out != 1)
			dup2(mini->arg->redirs->fd_out, STDOUT_FILENO);
	}
	path = ft_get_path(mini->arg->argv[0], mini->env);
	//printf("Path: %s\n", path);
	if (!mini->arg->argv || !mini->arg->argv[0]
		|| !ft_isalnum(mini->arg->argv[0][0]))
	{
		ft_memfree(path);
		path = mini->arg->argv[0];
	}
	if (!path)
		exit(127);
	execve(path, mini->arg->argv, envp);
	perror("execve");
	exit(127);
}

static void	handle_status(t_shell *mini)
{
	if (WIFEXITED(mini->status))
		mini->status = WEXITSTATUS(mini->status);
	if (mini && mini->status == 127)
		printf("%s: %s\n", mini->arg->argv[0], "command not found");
}

static void	ft_next_cmd(t_shell *mini)
{
	t_redir	*next;
	t_arg	*tmp;

	ft_memfree_all(mini->arg->argv);
	if (mini->arg->redirs)
	{
		ft_memfree(mini->arg->redirs->cmd);
		if (mini->arg->redirs->fd_in != 0)
			close(mini->arg->redirs->fd_in);
		if (mini->arg->redirs->fd_out != 1)
			close(mini->arg->redirs->fd_out);
		next = mini->arg->redirs;
		mini->arg->redirs = mini->arg->redirs->next;
		ft_memfree(next);
	}
	tmp = mini->arg;
	mini->arg = mini->arg->next;
	ft_memfree(tmp);
}

static void	child_process(t_shell *msh)
{
	if (msh->arg->redirs)
	{
		if (msh->arg->redirs->fd_in != STDIN_FILENO)
		{
			dup2(msh->arg->redirs->fd_in, STDIN_FILENO);
			close(msh->arg->redirs->fd_in);
		}
		if (msh->arg->redirs->fd_out != STDOUT_FILENO)
		{
			dup2(msh->arg->redirs->fd_out, STDOUT_FILENO);
			close(msh->arg->redirs->fd_out);
		}
	}
	if (msh->arg->pipe_in != STDIN_FILENO)
	{
		dup2(msh->arg->pipe_in, STDIN_FILENO);
		close(msh->arg->pipe_in);
	}
	if (msh->arg->pipe_out != STDOUT_FILENO)
	{
		dup2(msh->arg->pipe_out, STDOUT_FILENO);
		close(msh->arg->pipe_out);
	}
	if (is_comms(msh))
		ft_comms(msh);
	else
		run_cmd(msh);
	exit(127); // safety exit if exec fails
}

bool	init_pipes(t_shell *mini)
{
	t_arg	*current;
	int		pipefd[2];

	current = mini->arg;
	if (!current || !current->next)
		return (true); // no piping needed
	while (current && current->next)
	{
		if (pipe(pipefd) < 0)
			return (false);
		current->pipe_out = pipefd[1];
		current->next->pipe_in = pipefd[0];
		current = current->next;
	}
	return (true);
}

int	close_pipes(t_arg *current, int prev_fd_in)
{
	if (current->pipe_out != STDOUT_FILENO)
		close(current->pipe_out);
	if (current->pipe_in != STDIN_FILENO)
		close(current->pipe_in);
	if (prev_fd_in != -1 && prev_fd_in != STDIN_FILENO)
		close(prev_fd_in);
	prev_fd_in = current->pipe_in;
	return (prev_fd_in);
}

void	execute_pipeline(t_shell *mini)
{
	pid_t	pid;
	pid_t	last_pid;
	int		prev_fd_in;
	t_arg	*current;

	last_pid = -1;
	prev_fd_in = -1;
	if (!init_pipes(mini))
		error_message("failed init pipe");
	current = mini->arg;
	while (current) //total de listas generadas
	{
		pid = fork();
		if (pid < 0)
			error_message("error creating fork");
		if (pid == 0)
		{
			mini->arg = current;
			child_process(mini);
			exit(EXIT_FAILURE);
		}
		else
		{
			last_pid = pid;
			prev_fd_in = close_pipes(current, prev_fd_in);
		}
		current = current->next;
	}
	if (last_pid != -1)
		waitpid(last_pid, &mini->status, 0);
	while (wait(NULL) > 0)
		;
	handle_status(mini);
	ft_next_cmd(mini);
}

void	execute(t_shell *mini)
{
	pid_t	pid;

	while (mini->arg)
	{
		if (mini->arg->redirs)
		{
			if (!mini->arg->redirs->cmd || !mini->arg->redirs->cmd[0]
				|| !ft_isascii(mini->arg->redirs->cmd[0]))
			{
				mini->status = 1;
				break ;
			}
		}
		if (is_comms(mini))
			ft_comms(mini);
		else
		{
			pid = fork(); // lo necesitamos porque llama a child y mantiene en espere el proceso de reinicir Shell
			if (pid < 0)
				error_message("failed to fork\n");
			if (pid == 0)
				child_process(mini);
			else
				waitpid(pid, &mini->status, 0);
			handle_status(mini);
		}
		ft_next_cmd(mini);
	}
}

void	ft_cmd_exec(t_shell *mini)
{
	//printf("entering ft_cmd_execc\n");
	if (!mini || !mini->arg)
		return ;
	if (mini->arg && mini->arg->next)
		execute_pipeline(mini);
	else if (mini->arg && !mini->arg->next)
		execute(mini);
}
