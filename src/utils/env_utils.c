/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:04:03 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/04 17:12:17 by mamaratr         ###   ########.fr       */
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

void	ft_add_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static void	ft_free_env_node(t_env *node)
{
	if (!node)
		return;
	ft_memfree(node->env_name);
	ft_memfree(node->env_value);
	ft_memfree(node);
}

t_env	*ft_lst_new_env(char *name, char *value, int alloc)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	if (alloc)
	{
		new_node->env_name = ft_strdup(name);
		new_node->env_value = ft_strdup(value);
		if (!new_node->env_name || !new_node->env_value)
		{
			ft_free_env_node(new_node);
			return (NULL);
		}
	}
	else
	{
		new_node->env_name = name;
		new_node->env_value = value;
	}
	new_node->next = NULL;
	return (new_node);
}

void	ft_lst_env_init(t_env **env, char **envp)
{
	t_env	*new;
	int		i;
	char	*name;
	char	*value;

	if (!env || !envp)
		return ;
	i = 0;
	while (envp[i])
	{
		name = get_env_name(envp[i]);
		value = get_env_value(envp[i]);
		if (name && value)
		{
			new = ft_lst_new_env(name, value, 1);
			if (new)
				ft_add_back_env(env, new);
			else
			{
				ft_memfree(name);
				ft_memfree(value);
			}
		}
		ft_memfree(name);
		ft_memfree(value);
		i++;
	}
}
