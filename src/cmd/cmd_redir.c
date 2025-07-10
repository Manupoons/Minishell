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

void execute_redir(t_shell *msh)
{
	t_arg	*arg;
	
	arg = msh->arg;
	if (!arg)
		return ;
	if (arg->fd_out != -1)
	{
		if (dup2(arg->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed output redirection");
			close(arg->fd_out);
			exit(2);
		}
		close(arg->fd_out);
		arg->fd_out = -1;
	}
	if (arg->fd_in != -1)
	{
		if (dup2(arg->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2 failed input redirection");
			close(arg->fd_in);
			exit(2);
		}
		close(arg->fd_in);
		arg->fd_in = -1;
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

int	handle_heredoc(t_arg *arg, t_redir *redir)
{
	char	*line;
	int		fd;
	char	*filename;

	filename = generate_tmp_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
		return (free(filename), 0);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, redir->cmd) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	if (arg->fd_in != -1)
		close(arg->fd_in);
	arg->fd_in = open(filename, O_RDONLY);
	if (arg->fd_in == -1)
		return (0);
	unlink(filename);
	return(free(filename), 1);
}

int	open_infile(t_arg *arg, t_redir *redir)
{
	int	fd;

	if (arg->fd_in != -1)
		close(arg->fd_in);
	fd = open(redir->cmd, O_RDONLY);
	if (fd == -1)
		return (printf("-bash: %s: No such file or directory\n", redir->cmd), 0);
	arg->fd_in = fd;
	return(1);	
}

int	open_outfile(t_arg *arg, t_redir *redir)
{
	int	fd;

	if (arg->fd_out != -1)
		close(arg->fd_out);
	fd = open(redir->cmd, O_WRONLY | O_CREAT
		| O_TRUNC, 0644);
	if (fd == -1)
		return (0);	
	arg->fd_out = fd;
	return(1);	
}

int	open_append(t_arg *arg, t_redir *redir)
{
	int	fd;

	if (arg->fd_out != -1)
		close(arg->fd_out);
	fd = open(redir->cmd, O_WRONLY | O_CREAT
		| O_APPEND, 0644);
	if (fd == -1)
		return (0);
	arg->fd_out = fd;
	return(1);	
}
int	execute_redir_token(t_arg *args)
{
	t_redir	*redir;

	redir = args->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
		{
			if (!open_infile(args, redir))
				return (0);
		}
		else if (redir->type == TOKEN_REDIR_OUT)
		{
			if (!open_outfile(args, redir))
				return (0);
		}
		else if (redir->type == TOKEN_APPEND)
		{
			if (!open_append(args, redir))
				return (0);
		}
		else if (redir->type == TOKEN_HEREDOC)
		{
			if (!handle_heredoc(args, redir))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}
