/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:45 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/29 16:28:35 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	ft_pwd(t_shell *mini)
{
	char	*buf;

	mini->status = 0;
	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	ft_memfree(buf);
}
