/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:54:32 by jdorazio          #+#    #+#             */
/*   Updated: 2024/09/26 11:27:06 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_converting_int_to_str(int n, char *str, int num_digits)
{
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str[num_digits--] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[num_digits--] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		num_digits;
	char	*str;

	num_digits = ft_count_digits(n);
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	str = ft_calloc(num_digits + 1, sizeof(char));
	if (!str)
		return (NULL);
	return (ft_converting_int_to_str(n, str, num_digits));
}
