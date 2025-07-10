/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:14:03 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/09 16:10:50 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	ft_next_cmd(t_shell *mini)
{
	t_redir	*next;
	t_arg	*tmp;

	if (!mini->arg)
		return ;
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

void	execute_pipeline(t_shell *mini)
{
	pid_t	last_pid;
	t_arg	*curr;

	curr = mini->arg;
	while (curr)
	{
		if (!execute_redir_token(curr))
			{
				printf("Redir failed en pipeline\n");
				mini->status = 1;
				exit(1);
			}
		curr = curr->next;
	}
	last_pid = -1;
	if (!init_pipes(mini))
	{
		printf("failed init pipe");
		free_args(mini->arg);
		return ;	
	}
	execute_pipeline_commands(mini, &last_pid);
	if (last_pid != -1)
		waitpid(last_pid, &mini->status, 0);
	while (wait(NULL) > 0)
		;
	handle_status(mini);
	free_args(mini->arg);
	mini->arg = NULL;
}

static void	execute_pid(t_shell *mini)
{
	pid_t	pid;

	if (!execute_redir_token(mini->arg))
	{
		mini->status = 1;
		free_args(mini->arg);
		mini->arg = NULL;
		return;
	}
	g_signal = S_CMD;
	pid = fork();
	if (pid < 0)
	{
		free_args(mini->arg);
		return ;
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process(mini);
		exit(1);
	}
	else
	{
		waitpid(pid, &mini->status, 0);
		handle_status(mini);
	}
	free_args(mini->arg);
	mini->arg = NULL;
}

void	execute(t_shell *mini)
{
	while (mini->arg)
	{
		if ((!mini->arg->argv || !mini->arg->argv[0])  && !mini->arg->redirs)
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
