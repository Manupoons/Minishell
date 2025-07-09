/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:48:41 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/25 19:20:46 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

bool	init_pipes(t_shell *mini)
{
	t_arg	*current;
	int		pipefd[2];

	current = mini->arg;
	if (!current || !current->next)
		return (true);
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

void	execute_pipeline_commands(t_shell *mini, pid_t *last_pid)
{
	pid_t	pid;
	int		prev_fd_in;
	t_arg	*current;

	prev_fd_in = -1;
	current = mini->arg;
	while (current)
	{
		if (!execute_redir_token(current))
	{
		mini->status = 1;
		printf("execute_pipe\n");
		free_args(mini->arg);
		mini->arg = NULL;
		return;
	}
		pid = fork();
		if (pid < 0)
			printf("error creating fork");
		if (pid == 0)
		{
			mini->arg = current;
			child_process(mini);
			exit(EXIT_FAILURE);
		}
		else
		{
			*last_pid = pid;
			prev_fd_in = close_pipes(current, prev_fd_in);
		}
		current = current->next;
	}
}
