/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:27:23 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/29 18:58:26 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	**ft_env_to_array(t_shell *mini)
{
	int		len;
	t_env	*temp;
	char	**envp;
	char	*tmp_str;

	len = 0;
	temp = mini->env;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	envp = malloc(sizeof(char *) * (len + 1));
	temp = mini->env;
	len = 0;
	while (temp)
	{
		tmp_str = ft_strjoin(temp->env_name, "=");
		envp[len] = ft_strjoin(tmp_str, temp->env_value);
		ft_memfree(tmp_str);
		temp = temp->next;
		len++;
	}
	envp[len] = NULL;
	return (envp);
}

char	*ft_get_path(char *cmd, t_env *env)
{
	char	**paths;
	int		i;
	char	*temp_str;
	char	*path;

	while (env && ft_strncmp(env->env_name, "PATH", 4))
		env = env->next;
	if (!env || !env->env_value)
		return (NULL);
	paths = ft_split(env->env_value, ':');
	i = -1;
	while (paths[++i])
	{
		temp_str = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp_str, cmd);
		ft_memfree(temp_str);
		if (!access(path, X_OK))
		{
			ft_memfree_all(paths);
			return (path);
		}
		ft_memfree(path);
	}
	ft_memfree_all(paths);
	return (NULL);
}
