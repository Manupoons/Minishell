/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:48:10 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/04 18:50:40 by mamaratr         ###   ########.fr       */
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
