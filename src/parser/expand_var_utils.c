/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaratr <mamaratr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 12:54:10 by jdorazio          #+#    #+#             */
/*   Updated: 2025/07/12 17:41:51 by mamaratr         ###   ########.fr       */
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

t_arg	*handle_parse_errors(t_arg *head_arg, t_arg *curr_arg)
{
	if (head_arg)
		free_args(head_arg);
	else if (curr_arg)
		free_args(curr_arg);
	return (NULL);
}
