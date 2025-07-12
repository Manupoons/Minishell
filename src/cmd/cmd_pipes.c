/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:48:41 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/12 18:24:55 by jdorazio         ###   ########.fr       */
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

void	close_pipes(t_arg *current)
{
	if (current->pipe_out != STDOUT_FILENO && current->pipe_out != -1)
	{
		close(current->pipe_out);
		current->pipe_out = -1;
	}
	if (current->pipe_in != STDIN_FILENO && current->pipe_in != -1)
	{
		close(current->pipe_in);
		current->pipe_in = -1;
	}
}

static int	handle_fork(t_shell *mini, t_arg *current)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		mini->status = 1;
		return (-1);
	}
	if (pid == 0)
	{
		mini->arg = current;
		child_process(mini);
		exit(1);
	}
	return (pid);
}

void	execute_pipeline_commands(t_shell *mini, pid_t *last_pid)
{
	t_arg	*current;

	current = mini->arg;
	while (current)
	{
		*last_pid = handle_fork(mini, current);
		if (*last_pid < 0)
			return ;
		close_pipes(current);
		current = current->next;
	}
}
