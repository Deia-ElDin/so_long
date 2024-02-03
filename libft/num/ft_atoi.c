/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 21:58:06 by dehamad           #+#    #+#             */
/*   Updated: 2023/12/26 14:55:23 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "num.h"

static void	ft_isspace(const char **str)
{
	while ((**str >= 9 && **str <= 13) || **str == 32)
		(*str)++;
}

static int	ft_issign(const char **str)
{
	int	pos;
	int	neg;

	pos = 0;
	neg = 0;
	while (**str == '+' || **str == '-')
	{
		if (**str == '+')
			pos++;
		else if (**str == '-')
			neg++;
		(*str)++;
	}
	if ((pos == 1 && !neg) || (!pos && !neg))
		return (1);
	else if (neg == 1 && !pos)
		return (-1);
	else
		return (0);
}

static int	ft_isnumber(const char **str)
{
	int	nbr;
	int	prev_nbr;
	int	sign;

	nbr = 0;
	sign = ft_issign(str);
	while (ft_isdigit(**str))
	{
		prev_nbr = nbr;
		nbr = (nbr * 10) + (**str - '0');
		(*str)++;
		if (sign > 0 && prev_nbr > nbr && nbr != -2147483648)
			return (-1);
	}
	return (sign * nbr);
}

int	ft_atoi(const char *str)
{
	ft_isspace(&str);
	return (ft_isnumber(&str));
}
