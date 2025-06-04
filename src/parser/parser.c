/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:59:31 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/04 16:02:11 by mamaratr         ###   ########.fr       */
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

int	count_pipes(t_shell *mini)
{
	int		i;
	t_arg	*current;

	i = 0;
	current = mini->arg;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i - 1); // return (N - 1). We always have at least 1 pipe		
}

t_arg	*parse_tokens(t_token *tokens)
{
	t_arg	*head_arg;
	t_arg	*curr_arg;
	t_token	*curr_token;
	int		index;

	head_arg = NULL;
	curr_arg = NULL;
	curr_token = tokens;
	index = 0;
	while (curr_token)
	{
		if (!curr_arg && !(curr_token->type == TOKEN_PIPE))
		{
			curr_arg = init_arg(word_counter(curr_token));
			head_arg = curr_arg;
		}
		if (curr_token->type == TOKEN_WORD)
			index += handle_word_token(curr_arg, curr_token->token, index);
		else if (curr_token->type == TOKEN_PIPE)
			curr_arg = handle_pipe_token(curr_arg, curr_token->next, &index);
		else if (curr_token->type == TOKEN_REDIR_IN
			|| curr_token->type == TOKEN_REDIR_OUT
			|| curr_token->type == TOKEN_APPEND
			|| curr_token->type == TOKEN_HEREDOC)
			handle_redir_token(curr_arg, curr_token);
		curr_token = curr_token->next;
	}
	return (head_arg);
}

int	handle_word_token(t_arg *curr_arg, char *token, int index)
{
	curr_arg->argv[index] = strdup(token);
	return (1);
}

t_arg	*handle_pipe_token(t_arg *curr_arg, t_token *next_tokens, int *index)
{
	t_arg	*new;

	if (!curr_arg)
		error_message("pipe without command before it.\n");
	if (!next_tokens)
		error_message("pipe without command after it.\n");
	new = init_arg(word_counter(next_tokens));
	curr_arg->next = new;
	*index = 0;
	return (new);
}

void	handle_redir_token(t_arg *curr_arg, t_token *token)
{
	t_token	*file_token;
	t_redir	*redir;

	file_token = token->next;
	if (!file_token || file_token->type != TOKEN_WORD)
		error_message("Syntax error_ redirection without filename.");
	redir = malloc(sizeof(t_redir));
	if (!redir)
		error_message("failed to alloc.");
	redir->type = token->type;
	redir->cmd = ft_strdup(file_token->token);
	if (!redir->cmd)
		error_message("Memory allocation failed for redir->cmd.");
	redir->fd_in = -1;
	redir->fd_out = -1;
	if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
		redir->fd_in = 0;
	else if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_APPEND)
		redir->fd_out = 1;
	redir->next = NULL;
	// printf("Adding redirection:\n");
	// printf("  Type: %d\n", redir->type);
	// printf("  Filename: %s\n", redir->cmd);
	// printf("  fd_in: %d, fd_out: %d\n", redir->fd_in, redir->fd_out);
	append_to_parser(&(curr_arg->redirs), redir);
}

void	append_to_parser(t_redir **head, t_redir *redir)
{
	t_redir	*tmp;

	if (!redir)
		return ;
	if (!*head)
	{
		//printf("Initializing parser list with: %s\n", redir->cmd);
		*head = redir;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
	//printf("append to parser\n");
}
