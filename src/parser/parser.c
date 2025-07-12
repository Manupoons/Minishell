/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:59:31 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/12 12:09:52 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static t_arg	*handle_pipe_token(t_arg *curr_arg, t_token *next_tokens)
{
	t_arg	*new;

	if (!next_tokens || next_tokens->type == TOKEN_PIPE)
	{
		ft_putstr_fd("mini: syntax error near unexpected token `|'\n", 2);
		return (NULL);
	}
	new = init_arg();
	if (!new)
	{
		ft_putstr_fd("mini: failed to allocate pipe arg\n", 2);
		return (NULL);
	}
	curr_arg->next = new;
	return (new);
}

static int	handle_redir_token(t_arg *curr_arg, t_token *token)
{
	t_token	*file_token;
	t_redir	*redir;

	file_token = token->next;
	if (!file_token)
	{
		printf("mini: syntax error near unexpected token `newline'\n");
		return (2);
	}
	if (file_token->type != TOKEN_WORD)
	{
		printf("mini: syntax error near unexpected token `%s'\n", token->token);
		return (2);
	}
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (perror("failed to alloc"), 2);
	redir->type = token->type;
	redir->cmd = ft_strdup(file_token->token);
	if (!redir->cmd)
		return (free(redir), 2);
	redir->next = NULL;
	return (append_to_parser(&(curr_arg->redirs), redir), 0);
}

static void	process_word_token(t_arg **curr, t_token *token, t_env *env,
	int *status)
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
	int *status)
{
	if (token->type == TOKEN_WORD)
		process_word_token(curr_arg, token, env, status);
	else if (token->type == TOKEN_PIPE)
	{
		*curr_arg = handle_pipe_token(*curr_arg, token->next);
		if (!(*curr_arg))
		{
			*status = 2;
			return (1);
		}
	}
	else if (is_redir(token->type))
	{
		if (!(*curr_arg))
		{
			printf("redir with no arg");
			return (1);
		}
		*status = handle_redir_token(*curr_arg, token);
		if (*status == 2)
			return (1);
	}
	return (0);
}

t_arg	*parse_tokens(t_token *tokens, t_env *env, int *status)
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
			return (handle_parse_errors(head_arg, curr_arg));
		if (is_redir(curr_token->type) && curr_token->next)
			curr_token = curr_token->next;
		curr_token = curr_token->next;
	}
	return (head_arg);
}
