/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:16:16 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/10 12:15:13 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_free_env(t_env **env)
{
	t_env	*temp;

	while (*env)
	{
		temp = (*env)->next;
		ft_memfree((*env)->env_name);
		ft_memfree((*env)->env_value);
		ft_memfree((*env));
		*env = temp;
	}
	*env = NULL;
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->token);
		free(tokens);
		tokens = tmp;
	}
}

void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs->next;
		if (redirs->cmd)
			free(redirs->cmd);
		if (redirs->fd_in >= 0)
			close(redirs->fd_in);
		if (redirs->fd_out >= 0)
			close(redirs->fd_out);
		free(redirs);
		redirs = tmp;
	}
}

void	free_args(t_arg *args)
{
	t_arg	*tmp;

	while (args)
	{
		tmp = args->next;
		if (args->argv)
		{
			free_array_split(args->argv);
		}
		if (args->redirs)
			free_redirs(args->redirs);
		free(args);
		args = tmp;
	}
}

void	free_args_and_exit(t_arg *args, const char *msg)
{
	if (msg)
	{
		write(2, "minishell: ", 11);
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	free_args(args);
	exit(EXIT_FAILURE);
}
