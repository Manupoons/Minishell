/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:16:16 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/11 08:30:57 by jdorazio         ###   ########.fr       */
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

t_arg	*handle_parse_errors(t_arg *head_arg, t_arg *curr_arg)
{
	if (head_arg)
		free_args(head_arg);
	else if (curr_arg)
		free_args(curr_arg);
	return (NULL);
}
