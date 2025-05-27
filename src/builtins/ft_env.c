/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:37:46 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/27 17:04:13 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

void	ft_env(t_shell *mini)
{
	//int	status;
	int	i;
	
	i = 0;
	if (mini->arg->argv[i])
	{
		printf("env: %s: No such file or directory\n", mini->arg->argv[i]);
		return ;
	}
	
}