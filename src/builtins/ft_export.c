/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:09:09 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/02 10:11:12 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static t_env	*copy_list(t_env *list)
{
	t_env	*env;
	t_env	*temp;

	temp = list;
	env = NULL;
	while (temp)
	{
		if (!env)
			env = ft_lst_new_env(temp->env_name, temp->env_value, 1);
		else
			ft_add_back_env(&env, ft_lst_new_env(temp->env_name,
					temp->env_value, 1));
		temp = temp->next;
	}
	return (env);
}

static	t_env	*sort_list(t_env *list)
{
	t_env	*temp;
	t_env	*aux;

	temp = list;
	aux = ft_lst_new_env("", "", 0);
	while (list->next != NULL)
	{
		if (list->next && ft_strcmp(list->env_name, list->next->env_name) > 0)
		{
			aux->env_name = list->env_name;
			aux->env_value = list->env_value;
			list->env_name = list->next->env_name;
			list->env_value = list->next->env_value;
			list->next->env_name = aux->env_name;
			list->next->env_value = aux->env_value;
			list = list->next;
		}
		else
			list = list->next;
	}
	list = temp;
	ft_memfree(aux);
	return (list);
}

static void	ft_exp_no_arg(t_shell *mini)
{
	t_env	*env;
	t_env	*list;

	list = copy_list(mini->env);
	env = sort_list(list);
	while (env)
	{
		if (ft_strcmp(env->env_name, "_") == 0)
			printf(" \r");
		else if (env->env_value[0])
			printf("declare -x %s=\"%s\"\n", env->env_name, env->env_value);
		else
			printf("declare -x %s\n", env->env_name);
		env = env->next;
	}
	ft_free_list(&list);
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

void	ft_export(t_shell *mini)
{
	int	i;

	mini->status = 0;
	if (mini->arg->args_count == 1)
		ft_exp_no_arg(mini);
	else
	{
		i = 0;
		while (mini->arg->argv[++i])
		{
			if (check_export(mini->arg->argv[i]))
				add_arg_to_env(mini->arg->argv[i], mini);
			else
				mini->status = 1;
		}
	}
}
