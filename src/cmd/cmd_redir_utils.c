/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 08:20:19 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/11 08:36:48 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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
	return (free(filename), 1);
}

int	open_infile(t_arg *arg, t_redir *redir)
{
	if (arg->fd_in != -1)
		close(arg->fd_in);
	arg->fd_in = open(redir->cmd, O_RDONLY);
	if (arg->fd_in == -1)
		return (perror(redir->cmd), 0);
	return (dup2(arg->fd_out, STDIN_FILENO) != -1);
}

int	open_outfile(t_arg *arg, t_redir *redir)
{
	if (arg->fd_out != -1)
		close(arg->fd_out);
	arg->fd_out = open(redir->cmd, O_WRONLY | O_CREAT
			| O_TRUNC, 0644);
	if (arg->fd_out == -1)
		return (perror(redir->cmd), 0);
	return (dup2(arg->fd_out, STDOUT_FILENO) != -1);
}

int	open_append(t_arg *arg, t_redir *redir)
{
	int	fd;

	if (arg->fd_out != -1)
		close(arg->fd_out);
	fd = open(redir->cmd, O_WRONLY | O_CREAT
			|O_APPEND, 0644);
	if (fd == -1)
		return (0);
	arg->fd_out = fd;
	return (1);
}
