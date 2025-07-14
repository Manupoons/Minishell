/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:45 by mamaratr          #+#    #+#             */
/*   Updated: 2025/07/14 12:03:33 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_pwd(t_shell *mini)
{
	char	*buf;

	mini->status = 0;
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
		mini->status = 1;
		return ;
	}
	ft_putendl_fd(buf, 1);
	ft_memfree(buf);
}
