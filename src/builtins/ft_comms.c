/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:32:15 by mamaratr          #+#    #+#             */
/*   Updated: 2025/06/02 10:13:28 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	is_comms(t_shell *mini)
{
	if (!mini->arg || !mini->arg->argv || !mini->arg->argv[0])
		return (0);
	if (ft_strcmp(mini->arg->argv[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(mini->arg->argv[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(mini->arg->argv[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(mini->arg->argv[0], "export") == 0)
		return (1);
	else if (ft_strcmp(mini->arg->argv[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(mini->arg->argv[0], "env") == 0)
		return (1);
	else if (ft_strcmp(mini->arg->argv[0], "exit") == 0)
		return (1);
	else
		return (0);
}

void	ft_comms(t_shell *mini)
{
	if (!mini->arg || !mini->arg->argv || !mini->arg->argv[0])
		return ;
	if (ft_strcmp(mini->arg->argv[0], "echo") == 0)
		ft_echo(mini);
	else if (ft_strcmp(mini->arg->argv[0], "cd") == 0)
		ft_cd(mini);
	else if (ft_strcmp(mini->arg->argv[0], "pwd") == 0)
		ft_pwd(mini);
	else if (ft_strcmp(mini->arg->argv[0], "export") == 0)
		ft_export(mini);
	else if (ft_strcmp(mini->arg->argv[0], "unset") == 0)
		ft_unset(mini);
	else if (ft_strcmp(mini->arg->argv[0], "env") == 0)
		ft_env(mini);
	else if (ft_strcmp(mini->arg->argv[0], "exit") == 0)
		ft_exit(mini);
}
