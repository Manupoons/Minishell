/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:14:03 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/27 20:18:55 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	run_cmd(t_shell *mini)
{
	char	*path;
	char	**envp;
	
	envp = ft_env_to_array(mini);
	if (mini->parser->fd_in != 0)
	dup2(mini->parser->fd_in, STDIN_FILENO);
	if (mini->parser->fd_out != 1)
	dup2(mini->parser->fd_out, STDOUT_FILENO);
	path = ft_get_path(mini->arg->argv[0], mini->env);
	if (!ft_isalnum(mini->arg->argv[0][0]))
	{
		free(path);
		path = NULL;
	}
	if (!path)
		exit(127);
		execve(path, mini->arg->argv, envp);
	perror("execve");
	exit(127);
}

static void	child_process(t_shell *mini)
{
	if (is_comms(mini))
		ft_comms(mini);
	else
		run_cmd(mini);
}

static void	handle_status(t_shell *mini)
{
	if (WIFEXITED(mini->status))
		mini->status = WEXITSTATUS(mini->status);
	if (mini && mini->status == 127)
		printf("%s: %s\n", mini->arg->argv[0], "command not found");
	else if (WIFSIGNALED(mini->status))
	{
		int sig = WTERMSIG(mini->status);
		mini->status = 128 + sig;
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	}
}

void	ft_next_cmd(t_shell *mini)
{
	t_parser	*next;

	if (mini->parser)
	{
		next = mini->parser;
		mini->parser = mini->parser->next;
		free(next->cmd);
		free(next);
	}
}

void	ft_minishell(t_shell *mini)
{
	pid_t	pid;

	while (mini->parser)
	{
		if (!mini->parser->cmd || !ft_isascii(mini->parser->cmd[0]))
		{
			mini->status = 1;
			break ;
		}
		mini->arg = ft_split_shell(mini, mini->parser->cmd, ' ');
		if (!mini->arg || !mini->arg->argv[0])
		{
			ft_next_cmd(mini);
			continue ;
		}
		if (is_comms(mini))
			ft_comms(mini);
		else
		{
			pid = fork();
			if (pid == 0)
				child_process(mini);
			else
				waitpid(pid, &mini->status, 0);
			handle_status(mini);
		}
		ft_free_split(mini->arg);
		mini->arg = NULL;
		ft_next_cmd(mini);
	}
}