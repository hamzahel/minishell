/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:27:12 by hel-ayac          #+#    #+#             */
/*   Updated: 2020/02/07 16:32:59 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	unsigned int	strlen;
	size_t			i;
	char			tmp;

	if (!str)
		return (NULL);
	strlen = ft_strlen(str) - 1;
	i = 0;
	if (str[i] == '-')
		i++;
	while (i < strlen)
	{
		tmp = str[i];
		str[i] = str[strlen];
		str[strlen] = tmp;
		i++;
		strlen--;
	}
	return (str);
}
