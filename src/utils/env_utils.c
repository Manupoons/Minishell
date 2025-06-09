/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:04:03 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/09 19:06:14 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

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

t_env	*ft_lst_new_env(char *name, char *value)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->env_name = ft_strdup(name);
	new_node->env_value = ft_strdup(value);
	if (!new_node->env_name || !new_node->env_value)
	{
		ft_memfree(new_node->env_name);
		ft_memfree(new_node->env_value);
		ft_memfree(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

static void	free_name_value(char *name, char *value)
{
	ft_memfree(name);
	ft_memfree(value);
}

static void	init_pwd(t_shell *mini)
{
	char	*cwd;
	char	*oldpwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		oldpwd = ft_strjoin("OLDPWD=", cwd);
		if (oldpwd)
			add_arg_to_env(oldpwd, mini);
		ft_memfree(oldpwd);
		ft_memfree(cwd);
	}
}

void	ft_lst_env_init(t_shell *mini, char **envp)
{
	t_env	*new;
	int		i;
	char	*name;
	char	*value;

	if (!mini || !envp)
		return ;
	i = 0;
	while (envp[i])
	{
		name = get_env_name(envp[i]);
		value = get_env_value(envp[i]);
		if (name && value)
		{
			new = ft_lst_new_env(name, value);
			if (new)
				ft_add_back_env(&mini->env, new);
			else
				free_name_value(name, value);
		}
		free_name_value(name, value);
		i++;
	}
	init_pwd(mini);
}
