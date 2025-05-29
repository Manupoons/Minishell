/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:14:03 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/29 18:15:08 by mamaratr         ###   ########.fr       */
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
	t_parser	*next;

	ft_memfree(mini->parser->cmd);
	ft_memfree_all(mini->arg->argv);
	if (mini->parser->fd_in != 0)
		close(mini->parser->fd_in);
	if (mini->parser->fd_out != 1)
		close(mini->parser->fd_out);
	next = mini->parser;
	mini->parser = mini->parser->next;
	ft_memfree(next);
}

static void	child_proccess(t_shell *msh)
{
	if (is_comms(msh))
		ft_comms(msh);
	else
		run_cmd(msh);
}

void	ft_cmd_exec(t_shell *mini)
{
	pid_t	pid;

	if (!mini || !mini->parser || !mini->arg)
		return ;
	while (mini->parser)
	{
		if (!ft_isascii(mini->parser->cmd[0]))
		{
			mini->status = 1;
			break ;
		}
		mini->arg->argv = shell_split(mini, mini->parser->cmd, ' ');
		if (is_comms(mini))
			ft_comms(mini);
		else
		{
			pid = fork();
			if (pid == 0)
				child_proccess(mini);
			else
				waitpid(-1, &mini->status, 0);
			handle_status(mini);
		}
		ft_next_cmd(mini);
	}
}
