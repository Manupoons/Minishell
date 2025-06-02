/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:14:03 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/31 21:22:47 by jdorazio         ###   ########.fr       */
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
	printf("Path: %s\n", path);
	if (!mini->arg->argv || !mini->arg->argv[0] || !ft_isalnum(mini->arg->argv[0][0]))
	{
		ft_memfree(path);
		path = mini->arg->argv[0];
	}
	execve(path, mini->arg->argv, envp);
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

// static void	child_proccess(t_shell *msh, int *fd)
// {
// 	close(fd[0]);
// 	if (is_comms(msh))
// 		ft_comms(msh);
// 	else
// 		run_cmd(msh);
// }


static void	child_proccess(t_shell *msh, int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		dup2(fd_out, STDOUT_FILENO);

	// Close unused fds in child here if needed (not shown)
	if (is_comms(msh))
		ft_comms(msh);
	else
		run_cmd(msh);
	exit(127); // safety exit if exec fails
}

void	execute_pipelines(t_shell *mini)
{
	int		i;
	int		num_cmds;
	int		**pipes;
	pid_t	*pids;
	t_arg	*current;

	// Count commands
	num_cmds = 0;
	current = mini->arg;
	while (current)
	{
		num_cmds++;
		current = current->next;
	}
	printf("num_cmds [%d]\n", num_cmds); 
	if (num_cmds == 0)
		return ;

	// Allocate pipes: (num_cmds - 1) pipes, each has 2 fds
	pipes = malloc(sizeof(int *) * (num_cmds - 1));
	for (i = 0; i < num_cmds - 1; i++)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) == -1)
			error_message("failed to create pipe\n");
	}

	pids = malloc(sizeof(pid_t) * num_cmds);
	current = mini->arg;

	for (i = 0; i < num_cmds; i++)
	{
		int fd_in = (i == 0) ? STDIN_FILENO : pipes[i - 1][0];
		int fd_out = (i == num_cmds - 1) ? STDOUT_FILENO : pipes[i][1];

		pids[i] = fork();
		if (pids[i] < 0)
			error_message("failed to fork\n");

		if (pids[i] == 0)
		{
			// Child closes all pipe fds except the ones used for stdin/stdout
			for (int j = 0; j < num_cmds - 1; j++)
			{
				if (pipes[j][0] != fd_in)
					close(pipes[j][0]);
				if (pipes[j][1] != fd_out)
					close(pipes[j][1]);
			}

			mini->arg = current; // Set current command for child
			child_proccess(mini, fd_in, fd_out);
		}

		current = current->next;
	}

	// Parent closes all pipe ends
	for (i = 0; i < num_cmds - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	free(pipes);

	// Wait for all children and handle status
	for (i = 0; i < num_cmds; i++)
	{
		waitpid(pids[i], &mini->status, 0);
		handle_status(mini);
	}
	free(pids);
}

void	ft_cmd_exec(t_shell *mini)
{
	if (!mini || !mini->arg)
		return ;
	if (mini->arg && mini->arg->next)
		execute_pipelines(mini);
	while (mini->arg)
	{
		if (mini->arg->redirs)
			if (!mini->arg->redirs->cmd || !ft_isascii(mini->arg->redirs->cmd[0]))
			{
				mini->status = 1;
				break;
			}
		if (is_comms(mini))
			ft_comms(mini);
		else
		{
			pid_t pid = fork();
			if (pid < 0)
				error_message("failed to fork\n");
			if (pid == 0)
				child_proccess(mini, STDIN_FILENO, STDOUT_FILENO);
			else
				waitpid(pid, &mini->status, 0);
			handle_status(mini);
		}
		ft_next_cmd(mini);
	}
}
