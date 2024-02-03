/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfarr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 22:02:49 by dehamad           #+#    #+#             */
/*   Updated: 2024/01/27 18:22:23 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"

void	ft_pfarr(t_fmt *fmt)
{
	char	**arr;
	int		index;

	arr = va_arg(fmt->args, char **);
	index = 0;
	while (arr[index])
	{
		fmt->len += ft_strlen(arr[index]);
		ft_putstr_fd(arr[index++], fmt->fd);
	}
}
