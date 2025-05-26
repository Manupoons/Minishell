/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:24:06 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/26 18:31:13 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

void	ft_exit(char **argv)
{
    ft_putendl_fd("exit", 2);
    if (!argv[1])
        exit(1);
    ft_putendl_fd("exit: too many arguments", 2);
}