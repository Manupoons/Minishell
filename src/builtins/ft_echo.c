/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:50 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/26 18:21:33 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

void	ft_echo(char **argv)
{
	int i;

	i = 1;
	if (argv[i] && !ft_strncmp(argv[i], "-n", 2))
		i++;
 	while (argv[i])
	{
		ft_putstr_fd(argv[i++], STDOUT_FILENO);
		if (argv[i])
			ft_putchar_fd(32, STDOUT_FILENO);
	}
	if (!(argv[i] && !ft_strncmp(argv[i], "-n", 2)))
		ft_putchar_fd(10, STDOUT_FILENO);
}