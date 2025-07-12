/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:16 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/12 19:03:24 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	update_env_value_if_exists(t_env *env_list, const char *name,
							const char *new_value)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->env_name, name) == 0)
		{
			if (!env_list->env_value && !new_value)
				return (1);
			ft_memfree(env_list->env_value);
			env_list->env_value = ft_strdup(new_value);
			return (1);
		}
		env_list = env_list->next;
	}
	return (0);
}

void	add_arg_to_env(char *var, t_shell *mini)
{
	char	*name;
	char	*value;
	t_env	*new_env;

	name = get_env_name(var);
	value = get_env_value(var);
	if (!name)
	{
		ft_memfree(name);
		return ;
	}
	if (!update_env_value_if_exists(mini->env, name, value))
	{
		new_env = ft_lst_new_env(name, value);
		if (new_env)
			ft_add_back_env(&mini->env, new_env);
	}
	ft_memfree(name);
	ft_memfree(value);
}

int	check_export(char *argv)
{
	int		i;
	char	*name;

	i = 0;
	name = get_env_name(argv);
	if (ft_isdigit(name[i]) || !*name)
	{
		if (!*name)
			printf("export: `': not a valid identifier\n");
		else
			printf("export: %s: not a valid identifier\n", argv);
		return (ft_memfree(name), 0);
	}
	while (name[i])
	{
		if (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		else
		{
			printf("export: %s: not a valid identifier\n", argv);
			return (ft_memfree(name), 0);
		}
	}
	return (ft_memfree(name), 1);
}
