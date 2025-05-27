/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:37:46 by mamaratr          #+#    #+#             */
/*   Updated: 2025/05/26 18:40:36 by mamaratr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./minishell.h"

void	ft_env(char **argv)
{
	int		status;

    if (argv[1])
    {
        printf("env: %s: No such file or directory\n", argv[1]);
        return ;
    }
    
}