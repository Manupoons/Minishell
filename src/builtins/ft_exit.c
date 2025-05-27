/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:24:06 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/27 17:05:12 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

void	ft_exit(t_shell *mini)
{
	ft_putendl_fd("exit", 2);
	if (!mini->arg->argv[1])
		exit(1);
	ft_putendl_fd("exit: too many arguments", 2);
}