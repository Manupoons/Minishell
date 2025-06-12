/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:59:31 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/07 08:35:38 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static t_arg	*handle_pipe_token(t_arg *curr_arg, t_token *next_tokens,
								int *index)
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

static void	append_to_parser(t_redir **head, t_redir *redir)
{
	t_redir	*tmp;

	if (!redir)
		return ;
	if (!*head)
		*head = redir;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
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
	append_to_parser(&(curr_arg->redirs), redir);
}


static void	split_tokens(int *index, char **expanded, t_arg **curr)
{
	char	**splitted;
	int		j;

	splitted = ft_split(*expanded, ' ');
	free(expanded);
	if (!splitted)
		error_message("split failed");
	j = 0;
	while (splitted[j])
		(*curr)->argv[(*index)++] = ft_strdup(splitted[j++]);
	j = 0;
	while (splitted[j])
		free(splitted[j++]);
	free(splitted);
}


static void	process_word_token(t_arg **curr, t_token *token, int *index, t_env *env, int status)
{
	char	*expanded;

	expanded = expand(token, env, status);
	if (*index == 0 && ft_strchr(expanded, ' '))
		split_tokens(index, &expanded, curr);
	else
	{
		(*curr)->argv[*index] = expanded;
		(*index)++;
	}
}

static void	process_tokens(t_arg **curr_arg, t_token *token, int *index, t_env *env, int status)
{
	if (token->type == TOKEN_WORD)
		process_word_token(curr_arg, token, index, env, status);
	else if (token->type == TOKEN_PIPE)
	{
		*curr_arg = handle_pipe_token(*curr_arg, token->next, index);
		if (!(*curr_arg))
			error_message("pipe init failed");
	}
	else if (is_redir(token->type))
	{
		if (!(*curr_arg))
			error_message("redir with no arg");
		handle_redir_token(*curr_arg, token);
	}
}

t_arg	*parse_tokens(t_token *tokens, t_env *env, int status)
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
		if (!curr_arg && curr_token->type != TOKEN_PIPE)
		{
			curr_arg = init_arg(word_counter(curr_token));
			if (!curr_arg)
				error_message("init_arg failed");
			head_arg = curr_arg;
		}
		process_tokens(&curr_arg, curr_token, &index, env, status);
		if (is_redir(curr_token->type) && curr_token->next)
			curr_token = curr_token->next;
		curr_token = curr_token->next;
	}
	return (head_arg);
}
