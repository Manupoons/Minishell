/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:00:16 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/06 17:04:39 by mamaratr         ###   ########.fr       */
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
			ft_memfree(env->env_name);
			ft_memfree(env->env_value);
			env->env_name = name;
			env->env_value = value;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	add_arg_to_env(char *var, t_shell *mini)
{
	t_env	*env;
	char	*name;
	char	*value;

	if (!ft_strrchr(var, '='))
		return ;
	name = get_env_name(var);
	value = get_env_value(var);
	if (!check_variable(name, value, mini))
	{
		env = ft_lst_new_env(name, value, 0);
		ft_add_back_env(&mini->env, env);
	}
}

int	check_export(char *argv)
{
	int		i;
	char	*name;

	i = 0;
	name = get_env_name(argv);
	if (ft_isdigit(name[i]))
	{
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
