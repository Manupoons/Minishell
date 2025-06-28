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

static char	*replace_especial(char *expanded, int status, int *i)
{
	char	*joined;
	char	*status_str;

	status_str = ft_itoa(status);
	if (!status_str)
		return (NULL);
	joined = ft_strjoin(expanded, status_str);
	free(status_str);
	free(expanded);
	(*i)++;
	return (joined);
}

static char *replace_env_var(char *token_str, t_env *env, char *expanded_val, int *i)
{
	int		j;
	char	*var_name;
	char	*joined;
	char	*var_value_from_env;
	char	*value_to_join;

	j = *i;
	while (ft_isalnum(token_str[j]) || token_str[j] == '_')
		j++;
	var_name = ft_substr(token_str, *i, j - *i);
	var_value_from_env = get_env_value_by_name(env, var_name);
	if (!var_value_from_env || *var_value_from_env == '\0')
	{
		*i = j;
		return (free(var_name), NULL);
	}
	value_to_join = ft_strdup(var_value_from_env);
	if (!value_to_join)
		return (free(var_name), NULL);
	free(var_name);
	joined = ft_join_free(expanded_val, value_to_join);
	if (!joined)
		return (NULL);
	*i = j;
	return (joined);
}

static char *handle_dollar_expansion(char *token_str, t_env *env, int status, int *i, char *current_expanded)
{
	(*i)++;
	if (!token_str[*i])
		return (strjoin_char(current_expanded, '$'));
	else if (token_str[*i] == '?')
		return(replace_especial(current_expanded, status, i));
	else if (ft_isalpha(token_str[*i]) || token_str[*i] == '_')
		return(replace_env_var(token_str, env, current_expanded, i));
	else
		return(strjoin_char(current_expanded, '$'));
}

static char *expand_var_token(char *token_str, t_env *env, int status)
{
	int		i;
	char	*current_expanded;
	char	*temp_str;

	i = 0;
	current_expanded = ft_strdup("");
	if (!current_expanded)
		return (NULL);
	while (token_str[i])
	{
		if (token_str[i] == '$')
			temp_str = handle_dollar_expansion(token_str, env, status, &i, current_expanded);
		else
			temp_str = strjoin_char(current_expanded, token_str[i++]);
		if (!temp_str)
			return (free(current_expanded), NULL);
		current_expanded = temp_str;
	}
	return (current_expanded);
}

char *expand(t_token *token, t_env *env, int status, int *flag)
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
