/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:43:10 by jdorazio          #+#    #+#             */
/*   Updated: 2025/05/29 19:40:08 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	is_quotes(char c)
{
	return (c == 34 || c == 39);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	add_token(char *input, t_token **token_list, t_token_type type)
{
	t_token	*new;
	t_token	*current;

	new = (t_token *) malloc(sizeof(t_token));
	if (!new)
		error_message("Failed to alloc mem for token.");
	new->token = ft_strdup(input);
	if (!new->token)
		error_message("Failed to dup line.");
	new->type = type;
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
