/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42.madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:54:10 by jdorazio          #+#    #+#             */
/*   Updated: 2025/06/14 12:54:10 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*ft_join_free(char *dst, char *src)
{
	char	*temp;

	if (!dst || !src)
		return (free(src), free(dst), NULL);
	temp = ft_strjoin((char const *)dst, (char const *)src);
	free(dst);
	free(src);
	return (temp);
}

char	*strjoin_char(char *s, char c)
{
	char	str[2];
	char	*joined;

	str[0] = c;
	str[1] = '\0';
	joined = ft_strjoin(s, str);
	free(s);
	return (joined);
}

void	free_array_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
