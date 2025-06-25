/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:24:18 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/10 19:06:47 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_arg	*init_arg(void)
{
	t_arg	*arg_list;

	arg_list = malloc(sizeof(t_arg));
	if (!arg_list)
		return (NULL);
	arg_list->args_count = 0;
	arg_list->pipe_in = 0;
	arg_list->pipe_out = 1;
	arg_list->argv = NULL;
	arg_list->redirs = NULL;
	arg_list->next = NULL;
	return (arg_list);
}

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

int	is_redir(int type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

static void	update_existing_redir(t_redir *last, t_redir *redir)
{
		ft_memfree(last->cmd);
		last->cmd = redir->cmd;
		last->type = redir->type;
		ft_memfree(redir);
}

static void	append_to_end(t_redir **head, t_redir *redir)
{
	t_redir *current;

	if (!*head)
	{
		redir->next = NULL;
		*head = redir;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = redir;
	redir->next = NULL;	
}

void	append_to_parser(t_redir **head, t_redir *redir)
{
	t_redir	*current;
	t_redir	*last;

	last = NULL;
	if (!redir)
		return ;
	current = *head;
	while (current)
	{
		if (redir->type == current->type)
			last = current;
		current = current->next;
	}
	if (last)
	{
		update_existing_redir(last, redir);
		return ;
	}
	append_to_end(head, redir);
}


char **ft_add_to_argv(char **arr, char *new_str)
{
	char	**new_arr;
	int		old_count;
	int		i;

	old_count = 0;
	if (arr)
		while (arr[old_count])
			old_count++;
	new_arr = malloc(sizeof(char *) * (old_count + 2));
	if (!new_arr)
	{
		if (new_str)
			free(new_str);
		return (NULL);
	}
	i = -1;
	while (++i < old_count)
		new_arr[i] = arr[i];
	new_arr[old_count] = ft_strdup(new_str);
	new_arr[old_count + 1] = NULL;
	if (arr)
		free(arr); 
	return (new_arr);
}

void split_tokens(char **expanded, t_arg **curr)
{
	char	**splitted;
	int	 i;

	splitted = ft_split(*expanded, ' ');
	if (!splitted)
		return ;
	i = 0;
	while (splitted[i])
	{
		(*curr)->argv = ft_add_to_argv((*curr)->argv, splitted[i]);
		if (!(*curr)->argv)
		{
			free_array_split(splitted);
			printf("malloc failed to argv\n");
			return ;
		}
		(*curr)->args_count++;
		i++;
	}
	free_array_split(splitted);
}
