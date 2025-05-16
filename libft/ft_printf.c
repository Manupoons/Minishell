/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorazio <jdorazio@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:03:34 by jdorazio          #+#    #+#             */
/*   Updated: 2025/03/12 16:11:57 by jdorazio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_handle_char_str(char c, va_list ptr)
{
	if (c == 'c')
		return (ft_putchar_fd_pf(va_arg(ptr, int), 1));
	else if (c == 's')
		return (ft_putstr_fd_pf(va_arg(ptr, char *), 1));
	return (0);
}

int	ft_handle_int(char c, va_list ptr)
{
	if (c == 'u')
		return (ft_putnbr_fd_pf(va_arg(ptr, unsigned int), 1));
	else
		return (ft_putnbr_fd_pf(va_arg(ptr, int), 1));
	return (0);
}

int	ft_handle_hexa_pointer(char c, va_list ptr)
{
	void			*p;
	unsigned int	x;

	if (c == 'p')
	{
		p = va_arg(ptr, void *);
		if (!p)
			return (ft_putstr_fd_pf("(nil)", 1));
		ft_putstr_fd_pf("0x", 1);
		return (2 + ft_putnbr_base_pf((unsigned long long) p
				, "0123456789abcdef"));
	}
	else if (c == 'x')
	{
		x = va_arg(ptr, unsigned int);
		return (ft_putnbr_base_pf(x, "0123456789abcdef"));
	}
	else if (c == 'X')
	{
		x = va_arg(ptr, unsigned int);
		return (ft_putnbr_base_pf(x, "0123456789ABCDEF"));
	}
	return (0);
}

int	ft_handle_case(char c, va_list ptr)
{
	if (c == 'c')
		return (ft_handle_char_str(c, ptr));
	else if (c == 's')
		return (ft_handle_char_str(c, ptr));
	else if (c == 'p')
		return (ft_handle_hexa_pointer(c, ptr));
	else if (c == 'i' || c == 'd' || c == 'u')
		return (ft_handle_int(c, ptr));
	else if (c == 'x' || c == 'X')
		return (ft_handle_hexa_pointer(c, ptr));
	else if (c == '%')
		return (ft_putchar_fd_pf('%', 1));
	return (0);
}

int	ft_printf(char const *c, ...)
{
	va_list	ptr;
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	va_start(ptr, c);
	if (!c)
		return (-1);
	while (c[i])
	{
		if (c[i] == '%')
		{
			i++;
			count += ft_handle_case(c[i], ptr);
		}
		else
			count += ft_putchar_fd_pf(c[i], 1);
		i++;
	}
	return (count);
}
