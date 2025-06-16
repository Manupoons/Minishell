/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:56:25 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/06 16:59:47 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*get_env_name(char *name)
{
	int	i;

	i = 0;
	if (!name || *name == '\0')
		return (ft_strdup(""));
	while (name[i] && name[i] != '=' && name[i] != ' ')
		i++;
	return (ft_substr(name, 0, i));
}

char	*get_env_value(char *value)
{
	int		i;
	char	*val;
	int		len;
	char	*tmp;

	if (!value || *value == '\0')
		return (ft_strdup(""));
	i = 0;
	while (value[i] && value[i] != '=' && value[i] != ' ')
		i++;
	if (value[i] != '=')
		return (ft_strdup(""));
	len = ft_strlen(value) - (i + 1);
	val = ft_substr(value, i + 1, len);
	if (val && len >= 2 && val[0] == '"' && val[len - 1] == '"')
	{
		tmp = ft_substr(val, 1, len - 2);
		ft_memfree(val);
		return (tmp);
	}
	return (val);
}

char	*get_env_value_by_name(t_env *env, const char *name)
{
	while (env)
	{
		if (!ft_strcmp(env->env_name, name))
			return (env->env_value);
		env = env->next;
	}
	return (NULL);
}
