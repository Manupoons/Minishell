/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:40:05 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/06 12:41:28 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	word_counter(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != TOKEN_PIPE)
	{
		if (tokens->type == TOKEN_WORD)
			count++;
		else if (tokens->type == TOKEN_REDIR_IN
			|| tokens->type == TOKEN_REDIR_OUT
			|| tokens->type == TOKEN_APPEND
			|| tokens->type == TOKEN_HEREDOC)
		{
			if (tokens->next)
				tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (count);
}

t_arg	*init_arg(int count)
{
	t_arg	*arg_list;

	arg_list = malloc(sizeof(t_arg));
	if (!arg_list)
		return (NULL);
	arg_list->args_count = count;
	arg_list->argv = malloc(sizeof(char *) * (arg_list->args_count + 1));
	if (!arg_list->argv)
		return (NULL);
	arg_list->argv[count] = NULL;
	arg_list->pipe_in = 0;
	arg_list->pipe_out = 1;
	arg_list->redirs = NULL;
	arg_list->next = NULL;
	return (arg_list);
}

int	is_redir(int type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
			|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

// return (N - 1). We always have at least 1 pipe
// int	count_pipes(t_shell *mini)
// {
// 	int		i;
// 	t_arg	*current;

// 	i = 0;
// 	current = mini->arg;
// 	while (current)
// 	{
// 		i++;
// 		current = current->next;
// 	}
// 	return (i - 1);
// }
