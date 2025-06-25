/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:16 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/25 19:28:46 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	check_variable(char *name, char *value, t_shell *mini)
{
	t_env	*env;

	env = mini->env;
	if (!env)
		return (0);
	while (env)
	{
		if (!ft_strcmp(env->env_name, name))
		{
			env->env_name = ft_strdup(name);
			env->env_value = ft_strdup(value);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static int	update_env_value_if_exists(t_env *env_list, const char *name,
							const char *new_value)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->env_name, name) == 0)
		{
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
	if (!name || !value)
	{
		ft_memfree(name);
		ft_memfree(value);
		return ;
	}
	if (!update_env_value_if_exists(mini->env, name, value))
	{
		if (!check_variable(name, value, mini))
		{
			new_env = ft_lst_new_env(name, value);
			if (new_env)
				ft_add_back_env(&mini->env, new_env);
		}
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
	printf("NAME [%s]\n", name);
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
