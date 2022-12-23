/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 03:09:43 by hel-ayac          #+#    #+#             */
/*   Updated: 2020/02/07 16:29:35 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	tmp = (char *)malloc(ft_strlen((char *)s1) * sizeof(char) + 1);
	if (tmp == NULL)
		return (NULL);
	while (s1[i])
	{
		tmp[i] = s1[i];
		i++;
	}
	if (s1[i] == '\0')
		tmp[i] = '\0';
	return (tmp);
}
