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
void	execute_pipeline_commands(t_shell *mini, pid_t *last_pid)
{
	pid_t	pid;
	t_arg	*current;

	current = mini->arg;
	while (current)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			mini->status = 1;
			return ;
		}		
		if (pid == 0)
		{
			mini->arg = current;
			child_process(mini);
			exit(1);
		}
	else
	{
    *last_pid = pid;
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
    current = current->next;
	}

	}
}
