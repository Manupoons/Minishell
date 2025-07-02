/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 00:44:40 by jdorazio          #+#    #+#             */
/*   Updated: 2025/06/10 13:03:10 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static char	*replace_especial(int status, int *i)
{
	char	*status_str;

	status_str = ft_itoa(status);
	if (!status_str)
		return (NULL);
	(*i)++;
	return (status_str);
}

static char	*replace_env_var(char *token_str, t_env *env, int *i)
{
	int		j;
	char	*var_name;
	char	*var_value_from_env;

	j = *i;
	while (ft_isalnum(token_str[j]) || token_str[j] == '_')
		j++;
	var_name = ft_substr(token_str, *i, j - *i);
	var_value_from_env = get_env_value_by_name(env, var_name);
	*i = j;
	if (!var_value_from_env || *var_value_from_env == '\0')
		return (free(var_name), NULL);
	free(var_name);
	return (ft_strdup(var_value_from_env));
}

static char	*handle_dollar_expansion(char *str, t_env *env, int status, int *i)
{
	(*i)++;
	if (!str[*i])
		return (ft_strdup("$"));
	else if (str[*i] == '?')
		return (replace_especial(status, i));
	else if (ft_isalpha(str[*i]) || str[*i] == '_')
		return (replace_env_var(str, env, i));
	else
		return (ft_strdup("$"));
}

static char	*expand_var_token(char *token_str, t_env *env, int status)
{
	int		i;
	char	*current_expanded;
	char	*temp_str;
	char	*joined;

	i = 0;
	current_expanded = ft_strdup("");
	if (!current_expanded)
		return (NULL);
	while (token_str[i])
	{
		if (token_str[i] == '$')
			temp_str = handle_dollar_expansion(token_str, env, status, &i);
		else
			temp_str = strjoin_char(ft_strdup(""), token_str[i++]);
		if (!temp_str)
			return (free(current_expanded), NULL);
		joined = ft_join_free(current_expanded, temp_str);
		if (!joined)
			return (NULL);
		current_expanded = joined;
	}
	return (current_expanded);
}

char	*expand(t_token *token, t_env *env, int status, int *flag)
{
	char	*expanded_result;

	*flag = 0;
	if (ft_strchr(token->token, '$') && token->quote_type != '\'')
	{
		expanded_result = expand_var_token(token->token, env, status);
		if (!expanded_result)
			return (NULL);
		*flag = 1;
	}
	else
	{
		expanded_result = ft_strdup(token->token);
		if (!expanded_result)
			return (NULL);
	}
	return (expanded_result);
}
