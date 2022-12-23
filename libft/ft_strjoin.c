/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-ayac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 00:23:00 by hel-ayac          #+#    #+#             */
/*   Updated: 2020/02/07 16:31:40 by hel-ayac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	buffer = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, s1, len1 + 1);
	ft_strlcat(buffer, s2, len2 + len1 + 1);
	buffer[len2 + len1 + 1] = '\0';
	return (buffer);
}
