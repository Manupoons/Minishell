/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:59:31 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/10 18:57:54 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static t_arg	*handle_pipe_token(t_arg *curr_arg, t_token *next_tokens)
{
	t_arg	*new;

	if (!curr_arg)
		free_args_and_exit(curr_arg, "pipe without command before it.\n");
	if (!next_tokens)
		free_args_and_exit(curr_arg, "pipe without command after it.\n");
	new = init_arg();
	curr_arg->next = new;
	return (new);
}

static void	handle_redir_token(t_arg *curr_arg, t_token *token)
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

static void	process_word_token(t_arg **curr, t_token *token, t_env *env, int status)
{
	char	*expanded;
	int		flag;

	expanded = expand(token, env, status, &flag);
	if (!expanded)
		return ;
	if (ft_strchr(expanded, ' ') && flag == 1)
		split_tokens(&expanded, curr);
	else
	{
		(*curr)->argv = ft_add_to_argv((*curr)->argv, expanded);
		if (!(*curr)->argv)
		{
			free(expanded);
			printf("malloc failed\n");
			return ;
		}
		(*curr)->args_count++;
	}
	free(expanded); // This MUST be here to free the string returned by expand

}

static void	process_tokens(t_arg **curr_arg, t_token *token, t_env *env, int status)
{
	if (token->type == TOKEN_WORD)
		process_word_token(curr_arg, token, env, status);
	else if (token->type == TOKEN_PIPE)
	{
		*curr_arg = handle_pipe_token(*curr_arg, token->next);
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

	head_arg = NULL;
	curr_arg = NULL;
	curr_token = tokens;
	while (curr_token)
	{
		if (!curr_arg && curr_token->type != TOKEN_PIPE)
		{
			curr_arg = init_arg();
			if (!curr_arg)
				error_message("init_arg failed");
			head_arg = curr_arg;
		}
		process_tokens(&curr_arg, curr_token, env, status);
		if (is_redir(curr_token->type) && curr_token->next)
			curr_token = curr_token->next;
		curr_token = curr_token->next;
	}
	return (head_arg);
}
