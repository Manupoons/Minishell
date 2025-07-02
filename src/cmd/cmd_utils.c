/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:21:59 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/25 19:19:00 by jdorazio         ###   ########.fr       */
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
			if (dup2(redir->fd_in, STDIN_FILENO) == -1)
				perror("dup2 redir out");
			close(redir->fd_in);
			redir->fd_in = -1;
		}
		if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_APPEND)
		{
			if (dup2(redir->fd_out, STDOUT_FILENO) == -1)
				perror("dup2 redir out");
			close(redir->fd_out);
			redir->fd_out = -1;
		}
		redir = redir->next;
	}
}

void	handle_status(t_shell *mini)
{
	if (WIFEXITED(mini->status) && mini->arg && mini->arg->argv
		&& mini->arg->argv[0])
		mini->status = WEXITSTATUS(mini->status);
	if (mini && mini->status == 127)
		printf("%s: %s\n", mini->arg->argv[0], "command not found");
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

void	execute_redir_token(t_arg *args)
{
	t_redir	*redir;

	redir = args->redirs;
	if (!redir)
		return ;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_IN)
			redir->fd_in = open(redir->cmd, O_RDONLY);
		if (redir->type == TOKEN_REDIR_OUT)
			redir->fd_out = open(redir->cmd, O_WRONLY | O_CREAT
					| O_TRUNC, 0777);
		if (redir->type == TOKEN_APPEND)
			redir->fd_out = open(redir->cmd, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		if (redir->type == TOKEN_HEREDOC)
			handle_heredoc(redir);
		redir = redir->next;
	}
}
