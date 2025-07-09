/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:21:59 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/04 13:01:38 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	execute_redir(t_shell *msh)
{
	t_redir	*redir;

	redir = msh->arg->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
		{
			if (redir->fd_in != -1 && dup2(redir->fd_in, STDIN_FILENO) == -1)
				return ;
			close(redir->fd_in);
			redir->fd_in = -1;
		}
		if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_APPEND)
		{
			if (redir->fd_out != -1 && dup2(redir->fd_out, STDOUT_FILENO) == -1)
				return ;
			close(redir->fd_out);
			redir->fd_out = -1;
		}
		redir = redir->next;
	}
}

void	handle_status(t_shell *mini)
{
	int	status;

	if (WIFSIGNALED(mini->status))
	{
		status = WTERMSIG(mini->status);
		if (status == SIGINT)
		{
			g_signal = S_SIGINT_CMD;
			mini->status = 128 + SIGINT;
		}
		else if (status == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			mini->status = 128 + SIGQUIT;
		}
	}
	else if (WIFEXITED(mini->status))
	{
		mini->status = WEXITSTATUS(mini->status);
		g_signal = S_BASE;
	}
	if (mini->status == 127 && g_signal == S_BASE
		&& mini->arg && mini->arg->argv && mini->arg->argv[0])
		printf("%s: command not found\n", mini->arg->argv[0]);
}

char	*generate_tmp_filename(void)
{
	int		counter;
	char	*filename;
	char	*suffix;
	char	*base;

	counter = 0;
	base = "/tmp/minishell_heredoc_";
	suffix = ft_itoa(counter++);
	filename = ft_strjoin(base, suffix);
	free(suffix);
	return (filename);
}

void	handle_heredoc(t_redir *redir)
{
	char	*line;
	int		fd;
	char	*filename;

	filename = generate_tmp_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return ;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->cmd) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	redir->fd_in = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
}

int	execute_redir_token(t_arg *args)
{
	t_redir	*redir;

	redir = args->redirs;
	if (!redir)
		return (1);
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
		{
			redir->fd_in = open(redir->cmd, O_RDONLY);
			if (redir->fd_in == -1)
				return (perror(redir->cmd), 0);
		}
		if (redir->type == TOKEN_REDIR_OUT)
		{
			redir->fd_out = open(redir->cmd, O_WRONLY | O_CREAT
				| O_TRUNC, 0777);
			if (redir->fd_out == -1)
				return (perror(redir->cmd), 0);

		}
		if (redir->type == TOKEN_APPEND)
		{
			redir->fd_out = open(redir->cmd, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
			if (redir->fd_out == -1)
				return (perror(redir->cmd), 0);
		}
		if (redir->type == TOKEN_HEREDOC)
			handle_heredoc(redir);
		redir = redir->next;
	}
	return (1);
}
