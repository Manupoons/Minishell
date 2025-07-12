/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:52 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/12 12:10:04 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	ft_change_oldpwd(t_shell *mini)
{
	char	*oldpwd;
	char	*path;

	path = getcwd(NULL, 0);
	oldpwd = ft_strjoin("OLDPWD=", path);
	add_arg_to_env(oldpwd, mini);
	ft_memfree(oldpwd);
	ft_memfree(path);
}

static void	ft_change_pwd(t_shell *mini)
{
	t_env	*env;
	char	*pwd;

	env = mini->env;
	while (env)
	{
		if (ft_strncmp(env->env_name, "PWD", 3) == 0)
		{
			pwd = getcwd(NULL, 0);
			ft_memfree(env->env_value);
			env->env_value = ft_strdup(pwd);
		}
		env = env->next;
	}
	ft_memfree(pwd);
}

void	ft_cd(t_shell *mini)
{
	char	*path;

	path = NULL;
	if (mini->arg->args_count > 2)
		return (printf("cd: too many arguments\n"), (void) NULL);
	ft_change_oldpwd(mini);
	if (mini->arg->argv[1])
		path = ft_strdup(mini->arg->argv[1]);
	else if (!path)
		path = ft_strdup(getenv("HOME"));
	if (chdir(path))
	{
		printf("mini: cd: %s: %s\n", path, strerror(errno));
		mini->status = 1;
	}
	else
		ft_change_pwd(mini);
	ft_memfree(path);
}
