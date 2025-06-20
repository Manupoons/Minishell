/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:16:16 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/10 19:07:24 by mamaratr         ###   ########.fr       */
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

void	ft_free_list(t_env **env)
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
		free(redirs->cmd);
		free(redirs);
		redirs = tmp;
	}
}

void	free_args(t_arg *args)
{
	t_arg	*tmp;
	int		i;

	while (args)
	{
		tmp = args->next;
		if (args->argv)
		{
			i = 0;
			while (args->argv[i])
			{
				free(args->argv[i]);
				i++;
			}
			free(args->argv);
			if (args->redirs)
				free_redirs(args->redirs);
		}
		free(args);
		args = tmp;
	}
}

void	free_args_and_exit(t_arg *args, const char *msg)
{
	if (msg)
		fprintf(stderr, "minishell: %s\n", msg);
	free_args(args);
	exit(EXIT_FAILURE);
}

void	free_array_split(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
		free(arr[i++]);
	free(arr);
}
