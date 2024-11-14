/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:38:29 by shuwang           #+#    #+#             */
/*   Updated: 2024/06/03 13:38:32 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_fmt_specifier(const char *format, int i)
{
	char	next;

	if (!(format[i + 1]))
		return (0);
	if (!(format[i] == '%'))
		return (0);
	next = format[i + 1];
	if (next == 'c' || next == 's' || next == 'p')
		return (1);
	else if (next == 'd' || next == 'i' || next == 'u')
		return (1);
	else if (next == 'x' || next == 'X' || next == '%')
		return (1);
	return (0);
}

int	process_printf(const char *format, va_list args, int i, int c)
{
	while (format[i])
	{
		if (is_fmt_specifier(format, i))
		{
			if (format[i + 1] == 'c')
				c = c + ft_putchar_ptf(va_arg(args, int));
			else if (format[i + 1] == 's')
				c = c + ft_putstr_ptf(va_arg(args, const char *));
			else if (format[i + 1] == 'p')
				c = c + ft_putptr_ptf(va_arg(args, void *));
			else if (format[i + 1] == 'd' || format[i + 1] == 'i')
				c = c + ft_putnbr_ptf(va_arg(args, int), 0);
			else if (format[i + 1] == 'u')
				c = c + ft_putunbr_ptf(va_arg(args, unsigned int), 0);
			else if (format[i + 1] == 'X' || format[i + 1] == 'x')
				c = c + ft_putx_ptf(va_arg(args, unsigned int), format[i + 1]);
			else if (format[i + 1] == '%')
				c = c + ft_putchar_ptf('%');
			i++;
		}
		else
			c = c + ft_putchar_ptf(format[i]);
		i++;
	}
	return (c);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		c;

	c = 0;
	if (format == NULL)
		return (-1);
	va_start(args, format);
	c = process_printf(format, args, 0, 0);
	va_end(args);
	return (c);
}
