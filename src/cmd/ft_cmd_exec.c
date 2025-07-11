/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:14:03 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/11 08:34:14 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	ft_next_cmd(t_shell *mini)
{
	t_redir	*redir;
	t_redir	*tmp_redir;
	t_arg	*tmp_arg;

	if (!mini->arg)
		return ;
	if (mini->arg->fd_in != -1 && mini->arg->fd_in != STDIN_FILENO)
		close(mini->arg->fd_in);
	if (mini->arg->fd_out != -1 && mini->arg->fd_out != STDOUT_FILENO)
		close(mini->arg->fd_out);
	ft_memfree_all(mini->arg->argv);
	redir = mini->arg->redirs;
	while (redir)
	{
		if (redir->cmd)
			free(redir->cmd);
		tmp_redir = redir;
		redir = redir->next;
		free(tmp_redir);
	}
	mini->arg->redirs = NULL;
	tmp_arg = mini->arg;
	mini->arg = mini->arg->next;
	free(tmp_arg);
}

void	execute_pipeline(t_shell *mini)
{
	pid_t	last_pid;

	last_pid = -1;
	if (!init_pipes(mini))
	{
		printf("failed init pipe");
		free_args(mini->arg);
		return ;
	}
	execute_pipeline_commands(mini, &last_pid);
	if (last_pid != -1)
	{
		waitpid(last_pid, &mini->status, 0);
	}
	while (wait(NULL) > 0)
		;
	handle_status(mini);
}

static void	execute_pid(t_shell *mini)
{
	pid_t	pid;

	g_signal = S_CMD;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		mini->status = 1;
		return ;
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process(mini);
	}
	else
	{
		waitpid(pid, &mini->status, 0);
		handle_status(mini);
	}
}

void	execute(t_shell *mini)
{
	while (mini->arg)
	{
		if ((!mini->arg->argv || !mini->arg->argv[0]) && !mini->arg->redirs)
		{
			ft_next_cmd(mini);
			continue ;
		}
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
			execute_pid(mini);
		ft_next_cmd(mini);
	}
}

void	ft_cmd_exec(t_shell *mini)
{
	if (!mini->arg)
		return ;
	if (mini->arg && mini->arg->next)
	{
		mini->in_pipe = true;
		execute_pipeline(mini);
		mini->in_pipe = false;
	}
	else if (mini->arg && !mini->arg->next)
	{
		mini->in_pipe = false;
		execute(mini);
	}
}
