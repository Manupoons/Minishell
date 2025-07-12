/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:43:10 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/12 13:00:48 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	is_quotes(char c)
{
	if (c == 39)
		return (39);
	else if (c == 34)
		return (34);
	return (0);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

int	handle_space(char *input, int i)
{
	while (input[i] == ' ' || input[i] == '\t' || input[i] == '\n'
		|| input[i] == '\r' || input[i] == '\v' || input[i] == '\f')
		i++;
	return (i);
}

void	add_token(char *input, t_token **token_list, t_token_type type,
					char quote)
{
	t_token	*new;
	t_token	*current;

	new = (t_token *) malloc(sizeof(t_token));
	if (!new)
		return ;
	new->token = ft_strdup(input);
	new->type = type;
	new->quote_type = quote;
	new->next = NULL;
	if (!*token_list)
		*token_list = new;
	else
	{
		current = *token_list;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
