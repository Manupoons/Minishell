/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:45 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/27 17:06:25 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

void	ft_pwd(t_shell *mini)
{
	char	*buf;

	mini->status = 0;
	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
}