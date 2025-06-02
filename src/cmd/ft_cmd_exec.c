/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:14:03 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/02 20:05:11 by jdorazio         ###   ########.fr       */
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
	printf("prueba run \n");
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



static void	child_proccess(t_shell *msh)
{

	if (is_comms(msh))
		ft_comms(msh);
	else
		run_cmd(msh);
	//exit(127); // safety exit if exec fails
}

void	execute_pipeline(t_shell *mini)
{
	printf("piping\n");
	pid_t	pid;
	t_arg	*current;

	current = mini->arg;
	while (current) //total de listas generadas
	{
		// CREAR MULTIPLES PIPES
		if (init_pipes(current))
		
		pid = pid;
		if (pid < 0)
			error_message("error creating fork");
		if (pid == 0)
			child_proccess(mini);
		else
			waitpid(pid, &mini->status, 0);
		handle_status(mini);	
	}
	ft_next_cmd(mini);
}

void	execute(t_shell *mini)
{
	pid_t pid;
	
	printf("Execute\n");
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
			pid = fork(); // lo necesitamos porque llama a child y mantiene en espere el proceso de reinicir Shell
			 if (pid < 0)
			 	error_message("failed to fork\n");
			 if (pid == 0)
			 {
				
				child_proccess(mini);
			 }
			else
				waitpid(pid, &mini->status, 0);
			handle_status(mini);
		}
		ft_next_cmd(mini);
	}	
}


void	ft_cmd_exec(t_shell *mini)
{
	printf("entering ft_cmd_execc\n");
	if (!mini || !mini->arg)
		return ;
	if (mini->arg && mini->arg->next)
		execute_pipeline(mini);
	else
		execute(mini);	
}
