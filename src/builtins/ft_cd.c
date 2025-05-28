/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:52 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/28 17:52:12 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

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
		return (printf("cd: too many arguments\n"), (void)NULL);
	ft_change_oldpwd(mini);
	if (mini->arg->argv[1])
		path = ft_strdup(mini->arg->argv[1]);
	else if (!path)
		path = ft_strdup(getenv("HOME"));
	if (chdir(path))
		perror("cd");
	else
		ft_pwd(mini);
	ft_memfree(path);
	ft_change_pwd(mini);
}