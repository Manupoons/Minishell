/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:59:31 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/25 19:20:46 by jdorazio         ###   ########.fr       */
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

static int	handle_redir_token(t_arg *curr_arg, t_token *token)
{
	t_token	*file_token;
	t_redir	*redir;

	file_token = token->next;
	if (!file_token || file_token->type != TOKEN_WORD)
	{
		printf("- bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	redir = malloc(sizeof(t_redir));
	if (!redir)
		perror("failed to alloc.");
	redir->type = token->type;
	redir->cmd = ft_strdup(file_token->token);
	if (!redir->cmd)
		perror("Memory allocation failed for redir->cmd.");
	redir->fd_in = -1;
	redir->fd_out = -1;
	if (redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_HEREDOC)
		redir->fd_in = 0;
	else if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_APPEND)
		redir->fd_out = 1;
	redir->next = NULL;
	return (append_to_parser(&(curr_arg->redirs), redir), 0);
}

static void	process_word_token(t_arg **curr, t_token *token, t_env *env,
	int status)
{
	char	*expanded;
	int		flag;

	expanded = expand(token, env, status, &flag);
	if (!expanded || (expanded[0] == '\0' && token->quote_type == '\''))
	{
		free(expanded);
		return ;
	}
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
		free(expanded);
	}
}

static int	process_tokens(t_arg **curr_arg, t_token *token, t_env *env,
	int status)
{
	if (token->type == TOKEN_WORD)
		process_word_token(curr_arg, token, env, status);
	else if (token->type == TOKEN_PIPE)
	{
		*curr_arg = handle_pipe_token(*curr_arg, token->next);
		if (!(*curr_arg))
			printf("pipe init failed");
	}
	else if (is_redir(token->type))
	{
		if (!(*curr_arg))
		{
			printf("redir with no arg");
			return (1);
		}
		if (handle_redir_token(*curr_arg, token))
			return (1);
	}
	return (0);
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
				return (printf("init_arg failed"), NULL);
			head_arg = curr_arg;
		}
		if (process_tokens(&curr_arg, curr_token, env, status))
			return (NULL);
		if (is_redir(curr_token->type) && curr_token->next)
			curr_token = curr_token->next;
		curr_token = curr_token->next;
	}
	return (head_arg);
}

/*
### He eliminado esta sección del código para ajustarlo a norminette. 
### Estás listas se liberan más adelante en el código y por eso 
ya no parecen ser necesarias.
### Si da problema de leaks tener este codigo en cuenta
	if (process_tokens(&curr_arg, curr_token, env, status))
		{
			if (head_arg)
				free_args(head_arg);
			else if (curr_arg)
				free_args(curr_arg);
			return (NULL);
		}
*/
