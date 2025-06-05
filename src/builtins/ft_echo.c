/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:50 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/04 16:03:09 by mamaratr         ###   ########.fr       */
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

char	*expand_var(char *arg, t_env *env)
{
	char	*var_name;

	if (arg[0] != '$' || !arg[1])
		return (ft_strdup(arg)); // Not a variable or just "$"
	var_name = arg + 1; // skip '$'
	return (ft_strdup(get_env_value_by_name(env, var_name)));
}

void	ft_echo(t_shell *mini)
{
	int		i;
	char	*expanded_arg;

	mini->status = 0;
	i = 1;
	if (ft_strcmp(mini->arg->argv[i], "-n") == 0)
		i++;
	while (mini->arg->argv[i])
	{
		if (mini->arg->argv[i][0] == '$')
			expanded_arg = expand_var(mini->arg->argv[i], mini->env);
		else
			expanded_arg = ft_strdup(mini->arg->argv[i]);
		ft_putstr_fd(expanded_arg, STDOUT_FILENO);
		ft_memfree(expanded_arg);
		if (mini->arg->argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!(mini->arg->argv[1] && ft_strcmp(mini->arg->argv[1], "-n") == 0))
		ft_putchar_fd('\n', STDOUT_FILENO);
}
