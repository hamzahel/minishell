/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoussao <omoussao@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 02:43:48 by hel-ayac          #+#    #+#             */
/*   Updated: 2022/03/26 23:58:40 by omoussao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	lonmax(char *str, int si)
{
	if (ft_strncmp(str, "9223372036854775807", 19) > 0 && si)
		return (-1);
	else if (ft_strncmp(str, "9223372036854775808", 19) > 0 && !(si))
		return (0);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	i;
	int	si;
	int	counter;
	int	bg;

	result = 0;
	counter = 0;
	i = 0;
	si = 1;
	while (str[i] == '\t' || str[i] == '\r' || str[i] == '\v' || \
		str[i] == ' ' || str[i] == '\f' || str[i] == '\n')
		i++;
	if (str[i] == '-')
		si = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	bg = i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if ((counter++) >= 19 && lonmax((char *)&str[bg], si) != 1)
			return (-(si > 0));
	}
	return (result * si);
}
