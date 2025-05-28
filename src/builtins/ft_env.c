/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:37:46 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/28 16:28:11 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

void	ft_env(t_shell *mini)
{
	t_env	*env;
	
	if (mini->arg->args_count > 1)
	{
		printf("env: %s: No such file or directory\n", mini->arg->argv[1]);
		mini->status = 127;
		return ;
	}
	env = mini->env;
	while (env)
	{
		if (!ft_strncmp(env->env_name, "_\0", 2))
			printf("_=/usr/bin/env\n");
		else
			printf("%s=%s\n", env->env_name, env->env_value);
		env = env->next;
	}
	mini->status = 0;
}
