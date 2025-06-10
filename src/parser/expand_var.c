/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 00:44:40 by jdorazio          #+#    #+#             */
/*   Updated: 2025/06/09 00:44:40 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*get_env_value_by_name(t_env *env, const char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->env_name, name))
			return (env->env_value);
		env = env->next;
	}
	return ("");
}

static char	*strjoin_char(char *s, char c)
{
	char	str[2];
	char	*joined;

	str[0] = c;
	str[1] = '\0';
	joined = ft_strjoin(s, str);
	free(s);
	return (joined);
}

static char	*replace_especial(char *expanded, int status, int *i)
{
	char	*joined;
	char	*status_str;

	status_str =ft_itoa(status);
	if (!status_str)
		return (expanded);
	joined = ft_strjoin(expanded, status_str);
	free(status_str);
	free(expanded);
	(*i)++;
	return (joined);
}

static char	*replace_env_var(char *token, t_env *env, char *expanded, int *i)
{
	int		j;
	char	*joined;
	char	*var_name;
	char	*var_value;

	j = (*i);
	while (ft_isalnum(token[j]) || token[j] == '_')
		j++;
	var_name = ft_substr(token, (*i), j - (*i));
	if (!var_name)
		return (expanded);
	var_value = get_env_value_by_name(env, var_name);
	free(var_name);
	if (!var_value)
		return (expanded);
	joined = ft_strjoin(expanded, var_value);
	free(expanded);
	(*i) = j;
	return (joined);
}


static void	expand_var_token(char **expanded, char *token, t_env *env, int status)
{
	int		i;

	i = 0;
	*expanded = ft_strdup("");
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			if (!token[i])
				(*expanded) = strjoin_char((*expanded), '$');
			else if (token[i] == '?')
				(*expanded) = replace_especial((*expanded), status, &i);
			else if (ft_isalpha(token[i]) || token[i] == '_')
				(*expanded) = replace_env_var(token, env, (*expanded), &i);
			else
				(*expanded) = strjoin_char((*expanded), '$');
		}
		else
		{
			(*expanded) = strjoin_char((*expanded), token[i]);
			i++;
		}
	}
}


char	*expand(t_token *token, t_env *env, int status)
{
	char	*expanded;

	if (ft_strchr(token->token, '$') && token->quote_type != '\'')
		expand_var_token(&expanded, token->token, env, status);
	else
		expanded = ft_strdup(token->token);
	if (!expanded)
		error_message("token expansion failed");
	return (expanded);
}
